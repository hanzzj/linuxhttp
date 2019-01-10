   相较于udp协议，tcp最重要的区别就是面向连接，以数据包的形式来发送接收数据，由数据包来完成差错控制等机制。实现http客户端可以使用tcp的方式，集成到Menuos的方法和linuxudp实现机制一样，添加命令和对应操作函数即可。可以将www.github.com 作为参数写在程序内部，在获取到首页index.html之后进行打印输出就可以了。不过这里实际上使用了IP地址，因为socket不太支持URL的访问形式，但是使用IP地址可能会导致301问题（视具体网站而定），也就是重定向问题（不知道咋解决？网上都是使用gethostbyname函数，或者就是JAVA的处理机制，但是这样传入的参数不还是Ip地址吗，我这里使用的是ping命令得到IP地址，没有差别的，有的网站,比如博客园就不会出这个问题)，301问题实际上表示已经连接上了，故也可以看作连接成功的标志，这里就不再处理了。
   dev.c 对应路径-> linux-3.18.6/net/core/dev.c 然后对设备的相关操作都在里面。
   /linux-3.18.6/drivers/net/loopback.c 
   ip.h->ip_output.c ->ip_queue_xmit function
   ip_input.c ->ip_receive (function)
   
