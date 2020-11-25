#include <action_client_test/server_node.h>

using std::placeholders::_1;
using std::placeholders::_2;

ServerNode::ServerNode()
  : Node("action_test_server")
  , cb_group_mutually_exclusive_(this->create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive))
  , server_(rclcpp_action::create_server<Fibonacci>(this, "/fibonacci",
                                                    std::bind(&ServerNode::handleActionGoal, this, _1, _2),
                                                    std::bind(&ServerNode::handleActionCancel, this, _1),
                                                    std::bind(&ServerNode::handleActionAccepted, this, _1),
                                                    rcl_action_server_get_default_options(),
                                                    cb_group_mutually_exclusive_))
{
}

rclcpp_action::GoalResponse ServerNode::handleActionGoal(const rclcpp_action::GoalUUID& uuid, std::shared_ptr<const Fibonacci::Goal> goal)
{
  (void) uuid;
  (void) goal;
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse ServerNode::handleActionCancel(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle)
{
  (void) goal_handle;
  return rclcpp_action::CancelResponse::ACCEPT;
}

void ServerNode::handleActionAccepted(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle)
{
  std::thread{std::bind(&ServerNode::execute, this, _1), goal_handle}.detach();
}

void ServerNode::execute(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle)
{
  const auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<Fibonacci::Feedback>();
  auto & sequence = feedback->sequence;
  sequence.push_back(0);
  sequence.push_back(1);
  auto result = std::make_shared<Fibonacci::Result>();

  for (std::size_t i = 1; (i < static_cast<std::size_t>(goal->order)) && rclcpp::ok(); ++i) {
    if (goal_handle->is_canceling()) {
      result->sequence = sequence;
      goal_handle->canceled(result);
      return;
    }

//    std::this_thread::sleep_for(std::chrono::duration<double>(0.1));

    sequence.push_back(sequence[i] + sequence[i - 1]);
    goal_handle->publish_feedback(feedback);
  }

  if (rclcpp::ok())
  {
    result->sequence = sequence;
    goal_handle->succeed(result);
  }
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ServerNode>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  executor.remove_node(node);
  rclcpp::shutdown();
}
