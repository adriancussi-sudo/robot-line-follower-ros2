import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class EstadoNode(Node):

    def __init__(self):

        super().__init__('estado_node')

        self.subscription = self.create_subscription(
            String,
            '/vision',
            self.callback_vision,
            10)

        self.publisher_ = self.create_publisher(
            String,
            '/estado_robot',
            10)

    def callback_vision(self, msg):

        estado = String()

        if msg.data == "IZQUIERDA":

            estado.data = "GIRANDO_IZQUIERDA"

        elif msg.data == "DERECHA":

            estado.data = "GIRANDO_DERECHA"

        else:

            estado.data = "AVANZANDO"

        self.publisher_.publish(estado)

        self.get_logger().info(
            f'Estado: {estado.data}')


def main(args=None):

    rclpy.init(args=args)

    nodo = EstadoNode()

    rclpy.spin(nodo)

    nodo.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()