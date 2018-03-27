import argparse
from EpollServer import EpollServer

SERVER_HOST = '192.168.10.133'    

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Socket Server Example with Epoll')
    parser.add_argument('--port', action='store', dest='port', type=int, required=True)
    given_args=parser.parse_args()
    port=given_args.port
    server=EpollServer(host=SERVER_HOST, port=port)
    server.run()
    