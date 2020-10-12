#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <example_interfaces/action/fibonacci.hpp>

class ServerNode : public rclcpp::Node
{
public:
  using Fibonacci = example_interfaces::action::Fibonacci;
  using ServerGoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

  explicit ServerNode();

private:
  rclcpp_action::GoalResponse handleActionGoal(const rclcpp_action::GoalUUID& uuid, std::shared_ptr<const Fibonacci::Goal> goal);

  rclcpp_action::CancelResponse handleActionCancel(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle);

  void handleActionAccepted(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle);

  void execute(const std::shared_ptr<ServerGoalHandleFibonacci> goal_handle);

  rclcpp::callback_group::CallbackGroup::SharedPtr cb_group_mutually_exclusive_;
  rclcpp_action::Server<Fibonacci>::SharedPtr server_;
};
