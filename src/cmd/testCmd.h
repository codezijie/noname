#pragma once
#include <map>
#include <memory>
#include <string>
namespace App {

class BaseTestCmd {
public:
  BaseTestCmd() = default;
  ~BaseTestCmd() = default;

  virtual void GenFakeData() = 0;
  virtual bool Run() = 0;

private:
};

class TestCmdMgr {
public:
  TestCmdMgr();
  ~TestCmdMgr() = default;
  using cmdPair = std::pair<std::string, std::unique_ptr<BaseTestCmd>>;
  using cmdMap = std::map<std::string, std::unique_ptr<BaseTestCmd>>;

  void Initalize();
  BaseTestCmd *GetTestCmdByName(const std::string cmdName);

private:
  bool RegisterCmd(const std::string &cmdName,
                   std::unique_ptr<BaseTestCmd> &&cmdInterface);
  void RemoveCmd(const std::string &cmdName);
  cmdMap cmdMap_;
};

/**
 * @brief a demo is how to define a test cmd
 *
 */
class DemoTestCmd : public BaseTestCmd {
public:
  using BaseTestCmd::BaseTestCmd;
  virtual void GenFakeData() override;
  virtual bool Run() override;

private:
};

} // namespace App
