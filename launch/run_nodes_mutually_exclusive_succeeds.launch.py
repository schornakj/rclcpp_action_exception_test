from launch import LaunchDescription

from launch_ros import get_default_launch_description
import launch_ros.actions

def generate_launch_description():
    ld = LaunchDescription([
        launch_ros.actions.Node(node_name='server_node', package='action_test', node_executable='action_test_server_node', output='screen'),
        launch_ros.actions.Node(node_name='client_node', package='action_test', node_executable='action_test_client_node_multithread_mutually_exclusive', output='screen'),
    ])
    return ld
