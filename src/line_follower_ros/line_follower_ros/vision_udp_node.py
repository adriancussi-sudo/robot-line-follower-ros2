import socket

import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class VisionUDPNode(Node):

    def __init__(self):

        super().__init__('vision_udp_node')

        self.publisher_ = self.create_publisher(
            String,
            '/vision',
            10)

        self.sock = socket.socket(
            socket.AF_INET,
            socket.SOCK_DGRAM)

        self.sock.bind(("0.0.0.0", 8888))

        self.sock.setblocking(False)

        self.timer = self.create_timer(
            0.05,
            self.check_udp)

        self.get_logger().info(
            'Esperando UDP...')

    def check_udp(self):

        try:

            data, addr = self.sock.recvfrom(1024)

            texto = data.decode().strip()

            msg = String()

            msg.data = texto

            self.publisher_.publish(msg)

            self.get_logger().info(
                f'Publicado: {texto}')

        except BlockingIOError:

            pass


def main(args=None):

    rclpy.init(args=args)

    node = VisionUDPNode()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()