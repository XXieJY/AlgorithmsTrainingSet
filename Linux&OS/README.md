## Linux相关

* Linux相关的常见题目：    
  * linux常见命令
    * 文本处理（grep，awk，sed，tail）；
    * 操作系统管理
      * 文件管理命令（如：修改权限）
      * 网络管理命令
      * 进程管理命令（注意要了解到used，buf，cache代表意义、kill，find，cp等等）
      * 管道命令
  * 文件系统；
    * 软硬链接；
    * IO缓冲
  * 网络系统：
    * socket通信
    * TCP/UDP的支持
    * IO模型：
      * select, epoll, poll包括三者区别，内部原理实现？
      * 同步/异步、阻塞/非阻塞的特征;
  * Linux&c++
    * c++的编译：
      * 在Linux中一个目的函数的生成过程或者说编译过程是怎么样的
      * 编译有哪些方式
      * 那在linux中，对于一个已经动态编译后的文件，怎么查找出它用了哪些动态库？
      * Linux共享库的搜索路径先后顺序
      * 如果一个动态编译后的文件，可能缺少了某些动态库，我们应该怎么把它们添加上？

---

### Linux文件系统：

* 文件系统基本原理

* 文件I/O和缓冲

* 文件并发控制

#### 文件系统基本原理
* linux文件类型：普通文件(plain files) + 特殊文件类型(目录、 设备、管道、sockets、符号链接(软链接/硬链接))


* linux链接：[ref](https://www.ibm.com/developerworks/cn/linux/l-cn-hardandsymb-links/index.html)  
  * ln -s oldfile newfile 建立软连接;  ln oldfile newfile 建立硬连接; 命令stat查看inode号; 查找软链接 # find /home -lname data.txt; 查找硬链接：# find /home -samefile /home/harris/debug/test3/old.file;
  * 为解决文件的共享使用，Linux 系统引入了两种链接;
    * 链接(硬链接)：若一个 inode 号对应多个文件名，则称这些文件为硬链接; 可以看作许多文件名持有对硬盘上同一个文件的inode号(或者叫做引用);
      * 硬链接的特点包括：
        * 指向相同文件的硬链接有相同的inode和data block；
        * 只能对已存在的文件进行创建硬链接；
        * 不能对目录进行创建硬链接；
        * 删除一个硬链接不影响其他硬链接；
    * 符号链接(软链接): 软链接就是一个普通文件，只是数据块内容存放的是另一文件的路径名的指向。软链接拥有独立inode号以及用户数据块。
      * 软链接的特点包括：
        * 软链接有自己的文件属性及权限等；
        * 可对不存在的文件或目录创建软链接；* 软链接可以对目录创建；  
        * 创建软链接时，链接计数 i_nlink 不会增加；
        * 删除软链接并不影响被指向的文件，但若被指向的原文件被删除，则相关软连接被称为死链接


* 文件描述符：描述所有已打开的各类型文件（包括 管道、FIFO、socket、终端、设备和普通文件）。  
  * 文件描述符的值：代表当前文件描述符在进程的文件描述符表中的序号。
  * 多个文件描述符可以指向同一个已打开文件：(inode和真实文件才是一对一的映射)
    * 第一种：文件描述符是相同的，因此指向相同的文件句柄，从而指向相同的Inode。
    * 第二种：文件描述符不同，指向不同的文件句柄，但是文件句柄却指向相同的Inode。
  * 文件描述符与I/O系统调用的关系：I/O系统调用的对象是文件描述符，即I/O操作都是应用于文件描述符上的。
  * 默认打开的标准文件描述符：用shell打开程序时，被打开的进程会继承shell的三个标准文件描述符0,1,2， 分别表示：表示标准输入／标准输出／标准错误。
  * 文件描述符与已打开文件的关系：文件描述符和文件是多对一映射的关系。可以有多个不同的文件描述符指向同一个已打开文件。


* 描述已打开文件的三张表。  
  * 进程级文件描述符表：储存每个进程已打开文件的文件描述符。每条文件描述符表项内容包括：当前进程打开对应文件时指定的flags。以及指向"系统已打开文件文件描述符表"的条目的指针。
  * 系统级文件表：保存打开文件句柄，用以描述所有已打开的文件。每条已打开文件句柄：存储描述打开文件的所有信息。其中重要的有：文件偏移量、状态标志、指向inode表的指针。所有已打开同一个文件的进程共享文件句柄，因此所有打开同一个文件的进程共享着：文件偏移量--》因此才会有文件追加数据时的原子性问题。tatus flags:指向inode表条目的指针：
  * 文件系统的inode表(不论打开文件这个概念，文件系统都需要维护一个唯一的inode表)：inode表每个条目包括：当前文件类型(regular file, socket, FIFO等等)和权限。指向当前文件拥有的锁的链表的指针。其他关于文件系统的metadata


#### 文件I/O缓冲

* 文件I/O接口：Open()打开；Close()关闭；Read()读文件；Write()写文件；lseek()偏移量读；

* 文件I/O时使用**用户空间缓冲和内核缓存区**：在文件I/O调用和文件底层之间有缓冲和缓存区。
  * 用户（进程）写时(调用write())： 系统调用(write())将数据写入内核空间的缓冲区中，随后某时刻内核将自己的缓冲写入硬盘。

  * 用户调用读(read())时：内核将文件数据读入自身缓冲区， 然后系统调用会从内核缓冲区中读取数据。


#### 文件IO并发控制，文件锁：[ref](https://www.ibm.com/developerworks/cn/linux/l-cn-filelock/)
Linux 支持的文件锁主要包括共享锁和排他锁（又称为读锁和写锁）。
* 共享锁可以多次加，而排他锁只能为一个进程独有。
* 文件加锁的系统调用包括：flock() 和 fcntl()；fcntl() 函数的功能很多，除了给文件加锁以外还可以改变已打开的文件的性质。


---

### Linux网络系统：
* Linux下socket编程

* Linux的并发模型：
  * 阻塞/非阻塞
  * 同步/异步
  * IO多路复用模式

* Linux的并发接口：select(), poll(), epoll();

#### Socket编程：
* Socket的类型：流socket(支持TCP)、数据报socket(支持UDP)

* Socket通信建立过程：
  * 流socket(TCP):
    * 服务端：
      1. 创建一个socket
      2. bind一个句柄（端口和地址）
      3. listen设置监听的客户数
      4. accept客户端的句柄
      5. 读写。（使用read()，write()，close()）
    * 客户机：
      1. 创建一个socket
      2. connect到服务器
      3. 读写操作。
  * 数据报socket(UDP):
    * 服务端：
      1. 创建一个socket
      2. bind一个句柄（端口和地址）
      3. 读写 （使用recvfrom()，sendto()，close()）
    * 客户机：
      1. 创建一个socket
      2. 读写操作

#### Linux并发模型：
[ref](http://www.cnblogs.com/fanzhidongyzby/p/4098546.html)
[ref2](http://blog.csdn.net/ithomer/article/details/5971779)

##### select和poll:
poll在1986年诞生于System V Release 3，它和select在本质上没有多大差别，但是poll没有最大文件描述符数量的限制。  
poll和select同样存在一个缺点就是，包含大量文件描述符的数组被整体复制于用户态和内核的地址空间之间，而不论这些文件描述符是否就绪，它的开销随着文件描述符数量的增加而线性增大。


##### 常见的IO并发模型有四种：
* 同步阻塞IO：即传统的IO模型。
```cpp
{  
    read(socket, buffer);//进程运行到这里阻塞直到读取结束  
    process(buffer);  
}
```

* 同步非阻塞IO：默认创建的socket都是阻塞的，非阻塞IO要求socket被设置为NONBLOCK。
```cpp
{
    while(read(socket, buffer) != SUCCESS); //这里read不阻塞进程，但需要while轮训；
    process(buffer);
}
```
* 同步阻塞IO多路复用：即select；**使用select以后最大的优势是用户可以在一个线程内同时处理多个socket的IO请求。用户可以注册多个socket，然后不断地调用select读取被激活的socket，即可达到在同一个线程内同时处理多个IO请求的目的。而在同步阻塞模型中，必须通过多线程的方式才能达到这个目的。**
```cpp
{
    select(socket);
    while(1) {
        sockets = select();
        for(socket in sockets) {
          if(can_read(socket)) {
            read(socket, buffer);
            process(buffer);
          }
      }
    }
}
```

* **同步非阻塞IO多路复用（参见epoll实现）**：即Reactor设计模式，有时也称为异步阻塞IO。通过Reactor的方式，可以将用户线程轮询IO操作状态的工作统一交给handle_events事件循环进行处理。用户线程注册事件处理器之后可以继续执行做其他的工作（异步），而Reactor线程负责调用内核的select函数检查socket状态。当有socket被激活时，则通知相应的用户线程（或执行用户线程的回调函数），执行handle_event进行数据读取、处理的工作。由于select函数是阻塞的，因此多路IO复用模型也被称为异步阻塞IO模型。注意，这里的所说的阻塞是指select函数执行时线程被阻塞，而不是指socket。一般在使用IO多路复用模型时，socket都是设置为NONBLOCK的，不过这并不会产生影响，因为用户发起IO请求时，数据已经到达了，用户线程一定不会被阻塞。
```cpp
void UserEventHandler::handle_event() {
    if(can_read(socket)) {
        read(socket, buffer);
        process(buffer);
    }
}
{
    Reactor.register(new UserEventHandler(socket));
}
```

* 异步非阻塞IO多路复用：即Proactor设计模式，也称为异步非阻塞IO。


##### IO多路复用模式：同步IO的Reactor和异步IO的Proactor；(Proactor和Reactor都是并发编程中的设计模式。)
  * I/O多路复用机制都依赖于一个事件多路分离器(Event Demultiplexer)。分离器对象可将来自事件源的I/O事件分离出来，并分发到对应的read/write事件处理器(Event Handler)。开发人员预先注册需要处理的事件及其事件处理器（或回调函数）；事件分离器负责将请求事件传递给事件处理器。

  * Reactor: 在Reactor中，事件分离器负责等待文件描述符或socket为读写操作准备就绪，然后将就绪事件传递给对应的处理器，最后由处理器负责完成实际的读写工作。

  * 而在Proactor模式中，处理器--或者兼任处理器的事件分离器，只负责发起异步读写操作。IO操作本身由操作系统来完成。


##### 常见命令：[ref](http://buptguo.com/2014/11/01/grep-awk-sed%E4%B8%8E%E6%AD%A3%E5%88%99%E8%A1%A8%E8%BE%BE%E5%BC%8F/)
* 文本处理（grep，awk，sed，tail）
  * awk文本处理工具:更适合处理以列分布为特点的文件;
  * grep则对文件进行过滤筛选信息。grep会对匹配一个或多个正则表达式的文本进行搜索，并只输出匹配（或者不匹配）的行或文本。
  * sed更多的处理文本行的更改、调整等操作;  
[awk](https://coolshell.cn/articles/9070.html)
[sed](https://coolshell.cn/articles/9104.html)
[grep](http://blog.jobbole.com/75410/)


* 文件管理命令：
  * 修改目录，文件权限和属主及数组命令
    * Chmod：用于改变指定文件的权限命令。 权限为 4 2 1, 所有者|组|其他人
    * Chown：用于改变文件拥有属性的命令。

  * 显示文件内容的命令  
    * Cat：用于显示指定文件的全部内容
      -n: 显示行号  
      -b: 显示行号且忽略空行  
    * More/Less：用分页的形式显示指定文件的内容，区别是more和less翻页使用的操作键不同。
    * Head：用于显示文件的前n行内容。
    * Tail：用于显示文件的后n行内容。
    * wc: 计数  
      -l: 行数  
      -w: 字数  
      -c: 字符数
    * tr  字符替换  
      ls | tr 'd' 'g'把d变成g  
      如果再使用-d 删除指定字符  ls | tr -d 'log'

  * 文件查找命令
    * Find：查找指定的文件。
    * Whereis：查找指定的文件源和二进制文件和手册等
    * Which：用于查询命令或别名的位置。
    * Locate：快速查找系统数据库中指定的内容。
    * file 察看文件类型  
    file test.sh
  * 文件连接命令
    * Ln为源文件创建一个硬连接。
    * Ln -s  为源文件创建一个软连接。

* 进程管理命令：
  * 查看内存使用情况：free

---

###


## 操作系统
（1） 进程与线程的区别和联系
（2） 一个进程可以创建多少线程，和什么有关
（3） 一个程序从开始运行到结束的完整过程（四个过程）
（4） 进程通信方法（Linux和windows下），线程通信方法（Linux和windows下）
（5） 进程调度方法详细介绍
（6） 页面置换方法详细介绍
（7） 能否实现一个LRU算法
（8） 死锁的必要条件（怎么检测死锁，解决死锁问题）
（9） 哲学家就餐，银行家，读者写者，生产者消费者（怎么加锁解锁，伪代码）
（10） 海量数据的bitmap使用原理
（11） 布隆过滤器原理与优点
（12） 布隆过滤器处理大规模问题时的持久化，包括内存大小受限、磁盘换入换出问题
（13） 同步IO和异步IO
（14） 文件读写使用的系统调用
（15） 线程池的了解、优点、调度处理方式和保护任务队列的方式
（16） 怎么回收线程
（17） 僵尸进程问题
（18） 多线程同步（尤其是如果项目中用到了多线程，很大可能会结合讨论）
（19） memcache了解
（20） 异常和中断的区别
（21） 一般情况下在Linux/windows平台下栈空间的大小
