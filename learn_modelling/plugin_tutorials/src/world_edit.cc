#include <sdf/sdf.hh>
#include <ignition/math/Pose3.hh>
#include "gazebo/gazebo.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/msgs/msgs.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/transport.hh"

/// \example examples/plugins/world_edit.cc
/// This example creates a WorldPlugin, initializes the Transport system by
/// creating a new Node, and publishes messages to alter gravity.
namespace gazebo
{
  class WorldEdit : public WorldPlugin
  {
    public: void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf)
    {
      // Create a new transport node
      transport::NodePtr node(new transport::Node());

      // Initialize the node with the world name
      // 用世界名初始化该指针，世界名允许节点与某个特定世界通信
      node->Init(_parent->Name());

      // Create a publisher on the ~/physics topic
      transport::PublisherPtr physicsPub = node->Advertise<msgs::Physics>("~/physics");

      // 新建ODE类型的物理属性消息
      msgs::Physics physicsMsg;
      physicsMsg.set_type(msgs::Physics::ODE);

      // Set the step time
      physicsMsg.set_max_step_size(0.01);

      // Change gravity
      msgs::Set(physicsMsg.mutable_gravity(), ignition::math::Vector3d(0.01, 0, 0.1));
      physicsPub->Publish(physicsMsg);
    }
  };

  // Register this plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(WorldEdit)
}