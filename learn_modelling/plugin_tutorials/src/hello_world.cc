#include <gazebo/gazebo.hh>

// 所有的插件都必须在gazebo的命名空间内
namespace gazebo
{
  class WorldPluginTutorial : public WorldPlugin //每个插件都必须继承自某个插件类型
  {
    public: WorldPluginTutorial() : WorldPlugin()
            {
              printf("Hello World!\n");
            }
    // 这儿的另一个强制函数是Load，它接受被加载的SDF文件内的元素和属性
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  // 该插件必须使用宏GZ_REGISTER_WORLD_PLUGIN在模拟器中注册，这个宏的唯一参数就是插件的类
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
}