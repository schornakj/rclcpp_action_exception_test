#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <example_interfaces/action/fibonacci.hpp>

class ClientNodeParallel : public rclcpp::Node
{
public:
  using Fibonacci = example_interfaces::action::Fibonacci;
  using ClientGoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

  explicit ClientNodeParallel();

private:
  void sendGoal();

  void asyncHandleClientReq(const std::size_t& order, const rclcpp_action::Client<Fibonacci>::SharedPtr& client);

  rclcpp::callback_group::CallbackGroup::SharedPtr cb_group_mutually_exclusive_;
  rclcpp_action::Client<Fibonacci>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::atomic_uint n_reqs_in_progress_;
  const std::size_t max_parallel_reqs_;
  std::atomic_uint n_completed_;
};
