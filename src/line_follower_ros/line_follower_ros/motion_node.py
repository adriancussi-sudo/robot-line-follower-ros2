import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from geometry_msgs.msg import TwistStamped

class MotionNode(Node):

    def __init__(self):

        super().__init__('motion_node')

        self.subscription = self.create_subscription(
            String,
            '/vision',
            self.callback_vision,
            10)

        self.publisher_ = self.create_publisher(
            TwistStamped,
            '/cmd_vel',
            10)

    def callback_vision(self, msg):

        cmd = TwistStamped()
        cmd.header.stamp = self.get_clock().now().to_msg()
        cmd.header.frame_id = "base_link"

        if msg.data == "IZQUIERDA":
            cmd.twist.linear.x = 0.5
            cmd.twist.angular.z = 0.0

        elif msg.data == "DERECHA":
            cmd.twist.linear.x = 0.5
            cmd.twist.angular.z = 0.0

        else:
            cmd.twist.linear.x = 0.5
            cmd.twist.angular.z = 0.0

        self.publisher_.publish(cmd)

        self.get_logger().info(
            f'Vision={msg.data} -> cmd_vel enviado')

def main(args=None):

    rclpy.init(args=args)

    nodo = MotionNode()

    rclpy.spin(nodo)

    nodo.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()