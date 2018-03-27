import socket
import select

class EpollServer:
    def __init__(self, host='localhost', port=0):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM,)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)     #非阻塞
        self.sock.bind((host,port))
        self.sock.listen(5)
        self.sock.setblocking(0)
        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)     #服务器套结字无缓存
        print('Started Epoll Server')
        self.epoll = select.epoll()
        self.epoll.register(self.sock.fileno(), select.EPOLLIN)             #加入epoll监听
    
    def run(self):
        try:
            clientsocks = {}
            requests = {}
            responses = {}
            while True:
                events = self.epoll.poll(1)
                for fileno, event in events:
                    if fileno == self.sock.fileno():
                        print('Server Accept!')
                        clientsock, address = self.sock.accept()
                        clientsock.setblocking(0)
                        self.epoll.register(clientsock.fileno(), select.EPOLLIN)
                        clientsocks[clientsock.fileno()] = clientsock       #设置字典，套结字描述符：套结字
                        requests[clientsock.fileno()] = b''                 #接受缓存
                        responses[clientsock.fileno()] = b''                #应答缓存
                    elif event & select.EPOLLIN:
                        requests[fileno] = clientsocks[fileno].recv(1024)  #接受信息
                        responses[fileno] = requests[fileno]
                        self.epoll.modify(fileno, select.EPOLLOUT)      #之后要修改,不能直接唤醒
                        print('Recv Data!' , requests[fileno])
                      # 此处开辟线程来具体处理，在线程内来接受消息，处理消息
                      # 这里fileno实际上是epolled，socket在clientsocks中
                      # 所以线程传参需要fileno和clientsocks[fileno]
                    elif event & select.EPOLLOUT:
                        print('Send Data!' , responses[fileno])
                        byteswritten = clientsocks[fileno].send(responses[fileno])  #发送信息
                        responses[fileno] = responses[fileno][byteswritten:]    #从发送完的位置到结束，及未发送部分赋值
                        self.epoll.modify(fileno, select.EPOLLIN)   #之后要修改,不能直接唤醒
                    #    if len(responses[fileno]) == 0:
                    #        self.epoll.modify(fileno, 0)                        #写完即不再关注
                    #        clientsocks[fileno].shutdown(socket.SHUT_RDWR)      #关闭读写
                    #elif event & select.EPOLLHUP:
                    else:
                        print('Error')
                        self.epoll.unregister(fileno)
                        clientsocks[fileno].close()
                        del clientsocks[fileno]
                        del responses[fileno]
                        del requests[fileno]
                    
        finally:
            self.epoll.unregister(self.sock.fileno())
            self.epoll.close()
            self.sock.close()
            
                        
