#include <functional>
#include <gazebo/gui/GuiIface.hh>
#include <gazebo/rendering/rendering.hh>
#include <gazebo/gazebo.hh>

namespace gazebo
{
  class SystemGUI : public SystemPlugin
  {
    // Destructor
    public: virtual ~SystemGUI()
    {
      this->connections.clear();
      if (this->userCam)
        this->userCam->EnableSaveFrame(false);
      this->userCam.reset();
    }

    // 在插件被构造后调用
    public: void Load(int /*_argc*/, char ** /*_argv*/)
    {
      this->connections.push_back(
          event::Events::ConnectPreRender(
            std::bind(&SystemGUI::Update, this)));
    }

    // 只在`Load`后调用一次
    private: void Init()
    {
    }

    // 每次PreRender事件都会调用，看`Load`函数
    private: void Update()
    {
      if (!this->userCam)
      {
        // 得到一个激活用户相机的指针
        this->userCam = gui::get_active_camera();

        // 开启帧的保存
        this->userCam->EnableSaveFrame(true);

        // 指定要保存帧的路径
        this->userCam->SetSaveFramePathname("/tmp/gazebo_frames");
      }

      // 得到scene的指针
      rendering::ScenePtr scene = rendering::get_scene();

      // 等待，直到scene被初始化了
      if (!scene || !scene->Initialized())
        return;

      // 通过名字寻找一个特定的图像
      if (scene->GetVisual("ground_plane"))
        std::cout << "Has ground plane visual\n";
    }

    // 申明用户相机的指针
    private: rendering::UserCameraPtr userCam;

    // 申明存储所有事件连接的vector
    private: std::vector<event::ConnectionPtr> connections;
  };

  // 和模拟器上注册插件
  GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}