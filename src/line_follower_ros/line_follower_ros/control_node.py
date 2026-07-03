import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class ControlNode(Node):

    def __init__(self):
        super().__init__('control_node')

        self.subscription = self.create_subscription(
            String,
            '/vision',
            self.callback_vision,
            10)

    def callback_vision(self, msg):

        self.get_logger().info(
            f'Recibido: {msg.data}')

def main(args=None):

    rclpy.init(args=args)

    nodo = ControlNode()

    rclpy.spin(nodo)

    nodo.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()