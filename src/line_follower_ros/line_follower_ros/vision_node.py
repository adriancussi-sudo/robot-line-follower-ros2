import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class VisionNode(Node):

    def __init__(self):
        super().__init__('vision_node')
        
        self.contador = 0

        self.publisher_ = self.create_publisher(
            String,
            '/vision',
            10)

        self.timer = self.create_timer(
            1.0,
            self.publicar)

    def publicar(self):

        msg = String()

        self.contador += 1

        if self.contador % 3 == 0:
            msg.data = "IZQUIERDA"
        elif self.contador % 3 == 1:
            msg.data = "CENTRO"
        else:
            msg.data = "DERECHA"

        self.publisher_.publish(msg)

        self.get_logger().info(
            f'Publicando: {msg.data}')

def main(args=None):

    rclpy.init(args=args)

    nodo = VisionNode()

    rclpy.spin(nodo)

    nodo.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()