# rclcpp_action_exception_test
Nodes to test various rclcpp_action bugs


## Exception Involved `UnawareGoalHandleError`

Run this launch file:
```
ros2 launch action_exception_test run_nodes_parallel.launch.py
```

This node sends a large number of `Fibonacci` action goals in parallel to an action server.

For me, it eventually throws an exception:
```
ros2 launch action_exception_test run_nodes_parallel.launch.py 
[INFO] [launch]: All log files can be found below /home/joe/.ros/log/2020-11-25-14-01-21-762074-yakshaver-19006
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [action_exception_test_server_node-1]: process started with pid [19028]
[INFO] [action_exception_test_client_node_parallel-2]: process started with pid [19029]
[action_exception_test_client_node_parallel-2] [INFO] [client_node]: N_IN_PROGRESS=0
[action_exception_test_client_node_parallel-2] [INFO] [client_node]: Action #1 succeeded! 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 

(many successful actions later...)

[action_exception_test_client_node_parallel-2] [INFO] [client_node]: Action #1121 succeeded! 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 
[action_exception_test_client_node_parallel-2] [INFO] [client_node]: N_IN_PROGRESS=39

[action_exception_test_client_node_parallel-2] terminate called after throwing an instance of 'rclcpp_action::exceptions::UnawareGoalHandleError'
[action_exception_test_client_node_parallel-2]   what():  Goal handle is not tracking the goal result.
[ERROR] [action_exception_test_client_node_parallel-2]: process has died [pid 27920, exit code -6, cmd '/home/joe/workspaces/cb_group_test_ws/install/action_exception_test/lib/action_exception_test/action_exception_test_client_node_parallel --ros-args -r __node:=client_node'].
```
