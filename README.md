# YamiBarai - 拳皇97一键出招

YamiBarai 是一个为《拳皇97》（The King of Fighters '97）设计的 C++ 程序，基于 Interception  Mabel，玩家通过按下 `G` 或 `H` 键，根据角色站位触发同一招式（通过宏定义选择八神庵的“暗拂”或陈国汉的“铁球飞押しつぶし”）。程序拦截键盘输入，模拟精确的按键序列，适合简化操作或练习连招。

## 功能
- **按键映射**：
  - 方向键：`W`（上）、`S`（下）、`A`（左）、`D`（右）。
  - 攻击键：`U`（轻拳，A）、`J`（轻脚，B）、`I`（重拳，C）、`K`（重脚，D）。
- **出招触发**：
  - 按 `G`：左站位（面向右），触发宏定义的招式。
  - 按 `H`：右站位（面向左），触发宏定义的招式。
- **支持招式**：
  - 八神庵 - 暗拂（↓↘→+C，即 S→D→I 或 S→A→I）。
  - 陈国汉 - 铁球飞押しつぶし（↓↙←+C，即 S→A→I 或 S→D→I）。
- **宏定义**：
  - `SKILL`：选择 `G` 和 `H` 触发的招式（0：暗拂，1：铁球飞押しつぶし）。
  - `DEBUG_LOG`：控制是否打印调试日志（1：启用，0：禁用）。
- 其他按键：原样转发，不影响游戏操作。

## 依赖项
- **Interception 库**：用于拦截和模拟键盘输入。
  - 下载地址：https://github.com/oblitum/Interception
  - 需要 `interception.h`、`interception.lib` 和 `interception.dll`。
- **MinGW**：C++ 编译器（推荐 MinGW-w64）。
- **CMake**：构建工具（版本 3.10 或更高）。
- **Windows**：程序依赖 Windows API 和 Interception 驱动。
- **拳皇97**：测试环境为《拳皇97》游戏（模拟器或原生版本）。

## 环境准备
1. **安装 Interception 驱动**：
   - 从 Interception 官网或 GitHub 下载驱动。
   - 以管理员权限运行 `install-interception.exe`。
   - 确保 `interception.dll` 放在可执行文件目录或系统路径（如 `C:\Windows\System32`）。

2. **安装 MinGW**：
   - 下载并安装 MinGW-w64（推荐通过 MSYS2 或直接下载）。
   - 确保 `g++` 和 `make` 命令可用（运行 `g++ --version` 确认）。

3. **安装 CMake**：
   - 下载并安装 CMake（https://cmake.org/download/）。
   - 确保 `cmake` 命令可用（运行 `cmake --version` 确认）。

4. **准备 Interception 库**：
   - 将 `interception.h` 放入项目目录或指定路径。
   - 将 `interception.lib` 放入链接路径。
   - 确保 `interception.dll` 在运行时可访问。

## 编译步骤
1. **创建项目目录**：
   - 将 `yamibarai.cpp` 放入项目目录（例如 `E:\project\yamibarai`）。

2. **创建 `CMakeLists.txt`**：
   - 在项目目录中创建以下 `CMakeLists.txt` 文件：
     ```cmake
     cmake_minimum_required(VERSION 3.10)
     project(yamibarai)

     set(CMAKE_CXX_STANDARD 11)
     set(CMAKE_CXX_STANDARD_REQUIRED ON)

     add_executable(yamibarai yamibarai.cpp)
     target_include_directories(yamibarai PRIVATE path/to/interception)
     target_link_libraries(yamibarai PRIVATE interception)
     ```
   - 将 `path/to/interception` 替换为 `interception.h` 和 `interception.lib` 的实际路径。

3. **编译项目**：
   - 打开终端（例如 PowerShell），进入项目目录：
     ```bash
     cd E:\project\yamibarai
     ```
   - 生成 Makefile：
     ```bash
     cmake -G "MinGW Makefiles" .
     ```
   - 编译并链接：
     ```bash
     mingw32-make
     ```
   - 成功后会生成 `yamibarai.exe`。

## 运行程序
1. **以管理员身份运行**：
   - Interception 库需要管理员权限。
   - 在 PowerShell 中以管理员身份运行：
     ```bash
     .\yamibarai.exe
     ```
   - 或右键 `yamibarai.exe`，选择“以管理员身份运行”。

2. **使用说明**：
   - 启动拳皇97（确保游戏窗口激活）。
   - 程序运行后，显示：
     ```
     YamiBarai injector running...
     Press G for left-side (facing right), H for right-side (facing left). Ctrl+C to exit.
     ```
   - 按 `G`：左站位（面向右），触发宏定义的招式（默认暗拂）。
   - 按 `H`：右站位（面向左），触发宏定义的招式（默认暗拂）。
   - 其他按键正常转发，不影响游戏操作。

3. **配置招式**：
   - 编辑 `yamibarai.cpp` 中的宏定义：
     ```cpp
     #define SKILL 0 // 0: 暗拂, 1: 铁球飞押しつぶし
     ```
   - 修改后重新编译。

4. **调试日志**：
   - 编辑 `yamibarai.cpp` 中的宏定义：
     ```cpp
     #define DEBUG_LOG 1 // 1: 启用调试日志, 0: 禁用调试日志
     ```
   - 启用日志时，控制台显示每次按键的扫描码和状态，方便调试。
   - 修改后重新编译。

5. **注意事项**：
   - 确保 Interception 驱动已安装。
   - 拳皇97的招式输入对时序敏感，可能需要调整 `yamibarai.cpp` 中的延时（`DELAY_DOWN=25` 等）。
   - 如果使用模拟器（如 MAME、Winkawaks），确认模拟器支持键盘输入且未屏蔽外部输入。
   - 代码基于 US 键盘布局，确认你的键盘布局一致（W, S, A, D, U, J, I, K）。

## 故障排查
- **编译失败**：
  - 确保 `interception.h` 和 `interception.lib` 路径正确。
  - 检查 MinGW 和 CMake 是否正确安装。
- **运行时错误**：
  - 如果提示“Failed to create Interception context”，确认 Interception 驱动已安装并以管理员身份运行。
  - 确保 `interception.dll` 在正确位置。
- **招式不生效**：
  - 检查延时设置（`DELAY_DOWN=25`、`DELAY_FORWARD=25`、`DELAY_PUNCH=15`），尝试调整为 `20` 或 `30`。
  - 确认拳皇97的输入窗口激活（游戏窗口需在前台）。
  - 在模拟器中检查键盘映射，确保 `S`（下）、`A`（左）、`D`（右）、`I`（重拳）正确对应游戏控制。
  - 启用调试日志（`DEBUG_LOG=1`）查看按键序列：
    ```cpp
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    ```

## 针对拳皇97的优化
- **调整延时**：
  - 拳皇97的招式输入窗口约为 15-30 帧（1 帧 ≈ 16.67ms）。当前延时（25+25+25+25+15+15=130ms）适配多数情况，建议测试后微调。
- **支持更多招式**：
  - 可添加其他招式（如八神庵的“鬼烧”：↓↘→+A，S→D→U）。
  - 示例：修改 `SKILL` 为新招式编号。
- **模拟器兼容性**：
  - 如果使用 MAME 或 Winkawaks，确认键盘映射：
    - `S` → 下，`A` → 左，`D` → 右，`I` → 重拳（C）。
  - 某些模拟器可能有输入延迟，尝试增加延时（如 `DELAY_DOWN=30`）。
- **站位判断**：
  - 玩家需手动判断角色站位（左站位用 `G`，右站位用 `H`）。
  - 未来可通过游戏内存读取自动检测站位（需额外开发）。

## 许可证
MIT License

Copyright (c) 2025 [Luway]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.