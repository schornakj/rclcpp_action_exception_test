# rclcpp_action_exception_test
Nodes to test a possible rclcpp_action bug

This succeeds:

```
ros2 launch action_exception_test run_nodes_mutually_exclusive_succeeds.launch.py
```
Console output:
```
ros2 launch action_exception_test run_nodes_mutually_exclusive_succeeds.launch.py 
[INFO] [launch]: All log files can be found below /home/joe/.ros/log/2020-10-12-12-08-54-944247-joe-313
[INFO] [launch]: Default logging verbosity is set to INFO
1602522534.947184 [2]       ros2: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[INFO] [action_exception_test_server_node-1]: process started with pid [340]
[INFO] [action_exception_test_client_node_multithread_mutually_exclusive-2]: process started with pid [341]
[action_exception_test_server_node-1] 1602522534.973522 [2] action_exc: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[action_exception_test_client_node_multithread_mutually_exclusive-2] 1602522534.978118 [2] action_exc: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Sending goal
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Action succeeded! 0 1 1 2 3 5 8 13 21 34 55 
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Sending goal
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Action succeeded! 0 1 1 2 3 5 8 13 21 34 55 
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Sending goal
[action_exception_test_client_node_multithread_mutually_exclusive-2] [INFO] [client_node]: Action succeeded! 0 1 1 2 3 5 8 13 21 34 55 
...
```


This crashes due to an uncaught exception:
```
ros2 launch action_exception_test run_nodes_reentrant_fails.launch.py
```
Console output:
```
ros2 launch action_exception_test run_nodes_reentrant_fails.launch.py
[INFO] [launch]: All log files can be found below /home/joe/.ros/log/2020-10-12-12-08-44-109224-joe-32669
[INFO] [launch]: Default logging verbosity is set to INFO
1602522524.112645 [2]       ros2: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[INFO] [action_exception_test_server_node-1]: process started with pid [32711]
[INFO] [action_exception_test_client_node_multithread_reentrant-2]: process started with pid [32712]
[action_exception_test_server_node-1] 1602522524.136421 [2] action_exc: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[action_exception_test_client_node_multithread_reentrant-2] 1602522524.138266 [2] action_exc: using network interface eno1 (udp/192.168.1.176) selected arbitrarily from: eno1, docker0, tun0
[action_exception_test_client_node_multithread_reentrant-2] [INFO] [client_node]: Sending goal
[action_exception_test_client_node_multithread_reentrant-2] terminate called after throwing an instance of 'std::runtime_error'
[action_exception_test_client_node_multithread_reentrant-2]   what():  Executing action client but nothing is ready
[ERROR] [action_exception_test_client_node_multithread_reentrant-2]: process has died [pid 32712, exit code -6, cmd '/home/joe/workspaces/cb_group_test_ws/install/action_exception_test/lib/action_exception_test/action_exception_test_client_node_multithread_reentrant --ros-args -r __node:=client_node'].
```
