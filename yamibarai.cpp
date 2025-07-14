#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "interception.h"
#include <random>
#include <functional>
#include <vector>
#include <string>

// —— 宏定义：控制是否打印调试日志 ——
// 1: 启用调试日志, 0: 禁用调试日志
#define DEBUG_LOG 0

// —— 扫描码定义（基于 US 键盘） ——
// 方向键
constexpr USHORT SC_W = 0x11; // 上
constexpr USHORT SC_S = 0x1F; // 下
constexpr USHORT SC_A = 0x1E; // 左
constexpr USHORT SC_D = 0x20; // 右
// 攻击键
constexpr USHORT SC_U = 0x16; // 轻拳 (A)
constexpr USHORT SC_J = 0x24; // 轻脚 (B)
constexpr USHORT SC_I = 0x17; // 重拳 (C)
constexpr USHORT SC_K = 0x25; // 重脚 (D)
// 触发键
constexpr USHORT SC_G = 0x22; // 左站位触发
constexpr USHORT SC_H = 0x23; // 右站位触发
// 数字键用于切换招式
constexpr USHORT SC_1 = 0x02; // 1
constexpr USHORT SC_2 = 0x03; // 2
constexpr USHORT SC_3 = 0x04; // 3
constexpr USHORT SC_4 = 0x05; // 4
constexpr USHORT SC_5 = 0x06; // 5
constexpr USHORT SC_6 = 0x07; // 6
constexpr USHORT SC_7 = 0x08; // 7
constexpr USHORT SC_8 = 0x09; // 8
constexpr USHORT SC_9 = 0x0A; // 9
constexpr USHORT SC_0 = 0x0B; // 0

// 延时单位
inline void ms(int t) { std::this_thread::sleep_for(std::chrono::milliseconds(t)); }

// —— 随机延时波动范围（毫秒）宏定义 ——
// 可根据需要调整，所有 ms_random 调用将自动应用此范围
#define RANDOM_DELAY_VARIATION 5

// 随机延时函数，范围[min_ms, max_ms]
inline void ms_random(int base_ms) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(base_ms - RANDOM_DELAY_VARIATION, base_ms + RANDOM_DELAY_VARIATION);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
}

// 延时常量（适配拳皇97）
const int DELAY_DOWN = 40;    // 方向键按下
const int DELAY_FORWARD = 40; // 方向键组合
const int DELAY_BACKWARD = 40; // 方向键组合
const int DELAY_PUNCH = 30;   // 拳/脚

// 八神庵 - 暗拂 (↓↘→+C)
void sendYamiBarai(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_punch = SC_I;
    InterceptionKeyStroke stroke{};
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_FORWARD);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 八神庵 - 八稚女 (↓↘→↘↓↙←+A/C)
void sendYaotome(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_backward = leftSide ? SC_A : SC_D;
    USHORT sc_punch = SC_I;

    InterceptionKeyStroke stroke{};

    // ↓
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // ↘（下+前）
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // 只松开下
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // →（只保留前）
    // 这里其实前已经按下，无需重复

    // ↘（下+前）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ↓（只保留下）
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // ↙（下+后）
    stroke.code = sc_backward; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ←（只保留后）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // 松开后
    stroke.code = sc_backward; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // 拳
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 七枷社 - 暗黑地狱极乐落 (→↘↓↙←→↘↓↙←+A)
void sendDarkHellParadiseDrop(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_right = leftSide ? SC_D : SC_A;
    USHORT sc_left = leftSide ? SC_A : SC_D;
    USHORT sc_down = SC_S;
    USHORT sc_punch = SC_U;

    InterceptionKeyStroke stroke{};

    // 第一圈：→↘↓↙←
    // →
    stroke.code = sc_right; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ↘（→不松，按下↓）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ↓（松开→，保留↓）
    stroke.code = sc_right; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // ↙（↓不松，按下←）
    stroke.code = sc_left; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ←（松开↓，保留←）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // 第二圈：→↘↓↙←
    // →
    stroke.code = sc_right; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ↘（→不松，按下↓）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ↓（松开→，保留↓）
    stroke.code = sc_right; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN);

    // ↙（↓不松，按下←）
    stroke.code = sc_left; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // ←（松开↓，保留←）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // 松开←
    stroke.code = sc_left; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD);

    // 轻拳
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

struct SkillEntry {
    std::string name;
    std::function<void(InterceptionContext, int, bool)> func;
};

int main() {
    // 招式列表，后续只需在这里添加新招式
    std::vector<SkillEntry> skills = {
        { "Iori Yagami - YamiBarai (Dark Thrust)", sendYamiBarai },
        { "Iori Yagami - Yaotome (Maiden Masher)", sendYaotome },
        { "Yashiro Nanakase - Dark Hell Paradise Drop", sendDarkHellParadiseDrop }
        // 继续添加新招式，如 { "xxx", sendXxx }
    };

    // 存储当前选择的招式索引
    int currentSkill = 1;

    std::cout << "YamiBarai - The King of Fighters '97 Move Injector\n";
    std::cout << "Press 1-" << skills.size() << " to select a move, G for left-side (facing right), H for right-side (facing left). Ctrl+C to exit.\n";
    for (size_t i = 0; i < skills.size(); ++i) {
        std::cout << (i + 1) << ": " << skills[i].name << "\n";
    }
    std::cout << "Current move: " << skills[currentSkill].name << "\n";

    InterceptionContext ctx = interception_create_context();
    if (!ctx) {
        std::cerr << "Failed to create Interception context\n";
        return -1;
    }
    interception_set_filter(ctx, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai injector running...\n";
    #endif
    while (true) {
        int device = interception_wait(ctx);
        InterceptionStroke stroke_raw{};
        InterceptionKeyStroke& stroke = *(InterceptionKeyStroke*)&stroke_raw;
        if (interception_receive(ctx, device, &stroke_raw, 1) <= 0) continue;
        USHORT code = stroke.code;
        USHORT state = stroke.state;
        #if DEBUG_LOG == 1
        std::cout << "Received: code=" << code << ", state=" << state << std::endl;
        #endif

        // 处理数字键切换招式
        if (state == INTERCEPTION_KEY_DOWN) {
            int selectedSkill = -1;
            if (code >= SC_1 && code <= SC_9) {
                selectedSkill = code - SC_1; // 1-9 映射到 0-8
            } else if (code == SC_0) {
                selectedSkill = 9; // 0 映射到 9
            }
            if (selectedSkill >= 0 && selectedSkill < static_cast<int>(skills.size())) {
                currentSkill = selectedSkill;
                std::cout << "Switched to move: " << skills[currentSkill].name << "\n";
                continue; // 拦截数字键，不发送到游戏
            }
        }

        // 处理 G/H 触发招式
        if ((code == SC_G || code == SC_H) && state == INTERCEPTION_KEY_DOWN) {
            bool leftSide = (code == SC_G);
            skills[currentSkill].func(ctx, device, leftSide);
            continue; // 拦截 G/H 键
        }

        // 其他按键透传
        interception_send(ctx, device, &stroke_raw, 1);
    }
    interception_destroy_context(ctx);
    return 0;
}