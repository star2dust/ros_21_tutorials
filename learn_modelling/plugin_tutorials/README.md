# Gazebo控制插件

当前的插件有6种类型：World，Model，Sensor，System，Visual，GUI

每个插件类型都被Gazebo的不同部分管理着，例如模型插件附加在某个模型上，并且控制该模型。相似地，世界插件，传感器插件也都需要特定的世界和传感器。系统插件在命令行中被指定，在Gazebo启动时首先加载，这一插件给用户在启动程序的控制。基于想实现的功能，我们应当选择不同的插件类型，比如我们想调整物理引擎，更改环境光，则需要世界插件。又或者想控制关节，和模型的状态，则需要模型插件。

## 代码编译和运行

- 编译代码：
```shell
mkdir build
cd build
cmake ../
make
```

- 运行前输入命令：
```shell
export GAZEBO_PLUGIN_PATH=$HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/build:$GAZEBO_PLUGIN_PATH
export GAZEBO_MODEL_PATH=$HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/urdf:$GAZEBO_MODEL_PATH
```

## 运行实例

- hello_world

```shell
gzserver $HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/config/hello.world --verbose
```
你应该能看到输出大概为：

```
Gazebo multi-robot simulator, version 9.16.0
Copyright (C) 2012 Open Source Robotics Foundation.
Released under the Apache 2 License.
http://gazebosim.org

[Msg] Waiting for master.
[Msg] Connected to gazebo master @ http://127.0.0.1:11345
[Msg] Publicized address: xxx.xxx.xxx.xxx
[Msg] Loading world file [/home/user/gazebo_plugin_tutorial/hello.world]
Hello World!
```

- model_push

以暂停形式`-u`运行仿真：

```shell
gzserver -u $HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/config/model_push.world
```

在另一个终端，启动GUI：
```shell
gzclient
```
点击play按钮，就能看到方盒沿x轴做匀速运动了。

- factory

在世界文件中，我们只添加了地平面，太阳和插件，现在运行Gazebo：

```shell
gazebo $HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/config/factory.world
```

你会发现Gazebo窗口出现的应该是一个球体、盒子、圆柱体排成一排的样子，这些物体来自`libfactory.so`。

- world_edit

改变世界重力大小方向，运行Gazebo：

```shell
gazebo $HOME/catkin_ws/src/learn_ros/learn_modelling/plugin_tutorials/config/world_edit.world
```

是不是发现世界中物体飘起来了？

- system_gui

在后台启动gzserver：

```shell
gzserver & 
```

运行gzclient和插件：

```shell
gzclient -g libsystem_gui.so
```

在`tmp/gazebo_frames`目录下，应该会出现一些照片。

最后，不要忘记终止后台运行的程序，在同一个终端输入

```shell
fg
```

即可把进程带到前台。按Ctrl+C终止进程。