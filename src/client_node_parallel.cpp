#include <action_client_test/client_node_parallel.h>

using std::placeholders::_1;
using std::placeholders::_2;

ClientNodeParallel::ClientNodeParallel()
  : Node("action_test_client_node")
  , cb_group_mutually_exclusive_(create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive))
  , client_(rclcpp_action::create_client<Fibonacci>(this, "/fibonacci", cb_group_mutually_exclusive_))
  , timer_(create_wall_timer(std::chrono::duration<double>(0.1), std::bind(&ClientNodeParallel::sendGoal, this)))
  , n_reqs_in_progress_{0}
  , max_parallel_reqs_{30}
{
}

void ClientNodeParallel::sendGoal()
{
  RCLCPP_INFO_STREAM(get_logger(), "N_IN_PROGRESS=" << n_reqs_in_progress_);

  if (n_reqs_in_progress_ < max_parallel_reqs_)
  {
    std::thread{std::bind(&ClientNodeParallel::asyncHandleClientReq, this, _1, _2), 15, client_}.detach();
  }
}

void ClientNodeParallel::asyncHandleClientReq(const std::size_t& order, const rclcpp_action::Client<example_interfaces::action::Fibonacci>::SharedPtr& client)
{
  n_reqs_in_progress_++;

  example_interfaces::action::Fibonacci::Goal goal;
  goal.order = order;

  rclcpp_action::Client<example_interfaces::action::Fibonacci>::SendGoalOptions options;
  options.goal_response_callback = [](std::shared_future<ClientGoalHandleFibonacci::SharedPtr> future) { (void) future; };
  options.result_callback = [](const ClientGoalHandleFibonacci::WrappedResult& result) { (void) result; };

  std::shared_future<ClientGoalHandleFibonacci::SharedPtr> gh_future;
  {
    client_mutex_.lock();
    gh_future = client->async_send_goal(goal, options);
    client_mutex_.unlock();
  }
  gh_future.wait();

  std::shared_future<ClientGoalHandleFibonacci::WrappedResult> async_res_future;
  {
    client_mutex_.lock();
    async_res_future = gh_future.get()->async_result();
    client_mutex_.unlock();
  }
  async_res_future.wait();

  auto result = async_res_future.get();

  if (result.code != rclcpp_action::ResultCode::SUCCEEDED)
  {
    RCLCPP_ERROR(get_logger(), "Action did not succeed");
    return;
  }

  std::stringstream stream;
  for (auto& seq : result.result->sequence)
    stream << seq << " ";

  RCLCPP_INFO_STREAM(get_logger(), "Action succeeded! " << stream.str());

  n_reqs_in_progress_--;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ClientNodeParallel>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  executor.remove_node(node);
  rclcpp::shutdown();
}
