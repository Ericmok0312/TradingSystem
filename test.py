from pynng import Sub0


with Sub0() as s1:
    s1.subscribe("WebApp")
    s1.dial("tcp://localhost:8888")
    while(True):
        msg = s1.recv_msg()
        print(msg.bytes.decode())