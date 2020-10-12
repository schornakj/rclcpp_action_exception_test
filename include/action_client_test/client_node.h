#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <example_interfaces/action/fibonacci.hpp>

class ClientNode : public rclcpp::Node
{
public:
  using Fibonacci = example_interfaces::action::Fibonacci;
  using ClientGoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

  explicit ClientNode();

private:
  void sendGoal();

  rclcpp::callback_group::CallbackGroup::SharedPtr cb_group_reentrant_;
  rclcpp_action::Client<Fibonacci>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;

};
