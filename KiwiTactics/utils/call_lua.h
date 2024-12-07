//#include <iostream>
//#include <sol/sol.hpp>  // 引入 sol2 库
//
//// 定义 C++ 类
//class AIModel_Lua {
//public:
//    std::string model_name;
//    int a;  // 新增的 public 成员
//
//    AIModel_Lua(const std::string& name, int value = 0) : model_name(name), a(value) {}
//
//    void train() {
//        std::cout << "Training model: " << model_name << std::endl;
//    }
//
//    std::string predict(const std::string& input) {
//        return "Prediction for '" + input + "' using model: " + model_name;
//    }
//};
//
//void runLua(AIModel_Lua& model, const std::string& script) {
//    /*
//    -- script.lua
//    print("Before modification: " .. model.a)
//
//    -- 修改 C++ 对象成员变量 a
//    model.a = 42
//
//    print("After modification: " .. model.a)
//    */
//    sol::state lua;
//    lua.open_libraries(sol::lib::base, sol::lib::package);
//    // 将 C++ 对象传递给 Lua
//    lua.set("model", &model);
//    // 注册 AIModel_Lua 类型到 Lua，使得 Lua 可以正确处理 C++ 类
//    lua.new_usertype<AIModel_Lua>("AIModel_Lua",
//        "train", &AIModel_Lua::train,
//        "predict", &AIModel_Lua::predict,
//        "a", &AIModel_Lua::a,  // 暴露成员变量
//        "model_name", &AIModel_Lua::model_name  // 暴露成员变量
//    );
//    // 执行 Lua 脚本
//    try {
//        lua.script_file(script);
//        // 在脚本执行后，输出 C++ 对象成员变量 a 的值
//        std::cout << "C++ value of 'a' after Lua modification: " << model.a << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error running Lua script: " << e.what() << std::endl;
//    }
//}
//
//int testLua() {
//    // 创建 C++ 对象实例
//    AIModel_Lua model("AI Model", 10);
//    // 输出修改前的 'a'
//    std::cout << "Initial value of 'a' in C++: " << model.a << std::endl;
//    // 运行 Lua 脚本并传递对象
//    runLua(model, "script.lua");
//    return 0;
//}
//
//int add(int a, int b) {
//    return 2 * a + b;
//}
//
//void runLuaFromFile(sol::state& lua, const std::string& filename) {
//    try {
//        lua.script_file(filename);  // 执行 Lua 文件
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error running Lua script: " << e.what() << std::endl;
//    }
//}
//
//inline void push_CharacterInfo_to_lua(lua_State* L, CharacterInfo* info, std::string name)
//{
//    // Push Attacker to Lua table
//    lua_pushstring(L, name.c_str());
//    lua_newtable(L);  // 创建 Attacker 表
//    std::cout << "Pushed " << name << " table" << std::endl;
//    lua_pushstring(L, "id");
//    lua_pushinteger(L, info->id);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".id: " << info->id << std::endl;
//
//    lua_pushstring(L, "position_x");
//    lua_pushinteger(L, info->position_x);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".position_x: " << info->position_x << std::endl;
//
//    lua_pushstring(L, "position_y");
//    lua_pushinteger(L, info->position_y);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".position_y: " << info->position_y << std::endl;
//
//    lua_pushstring(L, "position_height");
//    lua_pushinteger(L, info->position_height);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".position_height: " << info->position_height << std::endl;
//
//    lua_pushstring(L, "direction");
//    lua_pushinteger(L, info->direction);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".direction: " << info->direction << std::endl;
//
//    lua_pushstring(L, "MaxHealth");
//    lua_pushinteger(L, info->MaxHealth);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MaxHealth: " << info->MaxHealth << std::endl;
//
//    lua_pushstring(L, "Health");
//    lua_pushinteger(L, info->Health);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Health: " << info->Health << std::endl;
//
//    lua_pushstring(L, "MaxMana");
//    lua_pushinteger(L, info->MaxMana);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MaxMana: " << info->MaxMana << std::endl;
//
//    lua_pushstring(L, "Mana");
//    lua_pushinteger(L, info->Mana);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Mana: " << info->Mana << std::endl;
//
//    lua_pushstring(L, "MaxArmor");
//    lua_pushinteger(L, info->MaxArmor);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MaxArmor: " << info->MaxArmor << std::endl;
//
//    lua_pushstring(L, "Armor");
//    lua_pushinteger(L, info->Armor);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Armor: " << info->Armor << std::endl;
//
//    lua_pushstring(L, "MaxActionPoint");
//    lua_pushinteger(L, info->MaxActionPoint);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MaxActionPoint: " << info->MaxActionPoint << std::endl;
//
//    lua_pushstring(L, "ActionPoint");
//    lua_pushinteger(L, info->ActionPoint);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".ActionPoint: " << info->ActionPoint << std::endl;
//
//    lua_pushstring(L, "MaxMovement");
//    lua_pushinteger(L, info->MaxMovement);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MaxMovement: " << info->MaxMovement << std::endl;
//
//    lua_pushstring(L, "Movement");
//    lua_pushinteger(L, info->Movement);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Movement: " << info->Movement << std::endl;
//
//    lua_pushstring(L, "Strength");
//    lua_pushinteger(L, info->Strength);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Strength: " << info->Strength << std::endl;
//
//    lua_pushstring(L, "PhyDef");
//    lua_pushinteger(L, info->PhyDef);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".PhyDef: " << info->PhyDef << std::endl;
//
//    lua_pushstring(L, "Intelligence");
//    lua_pushinteger(L, info->Intelligence);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Intelligence: " << info->Intelligence << std::endl;
//
//    lua_pushstring(L, "MagDef");
//    lua_pushinteger(L, info->MagDef);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".MagDef: " << info->MagDef << std::endl;
//
//    lua_pushstring(L, "Dexterity");
//    lua_pushinteger(L, info->Dexterity);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Dexterity: " << info->Dexterity << std::endl;
//
//    lua_pushstring(L, "CriticalRate");
//    lua_pushinteger(L, info->CriticalRate);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".CriticalRate: " << info->CriticalRate << std::endl;
//
//    lua_pushstring(L, "CriticalStrength");
//    lua_pushinteger(L, info->CriticalStrengh);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".CriticalStrength: " << info->CriticalStrengh << std::endl;
//
//    lua_pushstring(L, "Luck");
//    lua_pushinteger(L, info->Luck);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Luck: " << info->Luck << std::endl;
//
//    lua_pushstring(L, "Will");
//    lua_pushinteger(L, info->Will);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Will: " << info->Will << std::endl;
//
//    lua_pushstring(L, "HitRate");
//    lua_pushinteger(L, info->HitRate);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".HitRate: " << info->HitRate << std::endl;
//
//    lua_pushstring(L, "Evasion");
//    lua_pushinteger(L, info->Evasion);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Evasion: " << info->Evasion << std::endl;
//
//    lua_pushstring(L, "Jump");
//    lua_pushinteger(L, info->Jump);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".Jump: " << info->Jump << std::endl;
//
//    lua_settable(L, -3);  // 将 Attacker 表插入 DamageCalcuteInfo 表
//    std::cout << "Pushed " << name << " to DamageCalcuteInfo table" << std::endl;
//
//}
//inline void push_SpatialRelationship_to_lua(lua_State* L, SpatialRelationship* info, std::string name)
//{
//    // 将 Relative 转换为 Lua 表
//    lua_pushstring(L, name.c_str());
//    lua_newtable(L);  // 创建 Relative 表
//
//    lua_pushstring(L, "inSight");
//    lua_pushboolean(L, info->inSight);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".inSight: " << info->inSight << std::endl;
//    lua_pushstring(L, "inAttackRange");
//    lua_pushboolean(L, info->inAttackRange);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".inAttackRange: " << info->inAttackRange << std::endl;
//    lua_pushstring(L, "isBackStrike");
//    lua_pushboolean(L, info->isBackStrike);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".isBackStrike: " << info->isBackStrike << std::endl;
//    lua_pushstring(L, "isSideStrike");
//    lua_pushboolean(L, info->isSideStrike);
//    lua_settable(L, -3);
//    std::cout << "Pushed " << name << ".isSideStrike: " << info->isSideStrike << std::endl;
//
//    // lua_settable(L, -3);
//}
//inline void push_damage_info_to_lua_(lua_State* L, DamageCalcuteInfo* info) {
//    // 创建一个新的表来表示 DamageCalcuteInfo
//    lua_newtable(L);
//    push_CharacterInfo_to_lua(L, &info->Attacker, "Attacker");
//    push_CharacterInfo_to_lua(L, &info->Defender, "Defender");
//    push_SpatialRelationship_to_lua(L, &info->Relative, "Relative");
//    // lua_settable(L, -1);    // Lua after push info: 1
//    // lua_settable(L, -2);    // crash
//    lua_settable(L, -3);    // Lua after push info: 1 栈顶table
//    // lua_settable(L, -4);    // crash
//}
//inline void push_damage_info_to_lua(lua_State* L, DamageCalcuteInfo* info) {
//    // 创建 DamageCalcuteInfo 表
//    lua_newtable(L);
//
//    // 创建 Attacker 表
//    lua_newtable(L);
//    lua_pushstring(L, "id");
//    lua_pushnumber(L, info->Attacker.id);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_x");
//    lua_pushnumber(L, info->Attacker.position_x);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_y");
//    lua_pushnumber(L, info->Attacker.position_y);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_height");
//    lua_pushnumber(L, info->Attacker.position_height);
//    lua_settable(L, -3);
//    lua_pushstring(L, "direction");
//    lua_pushnumber(L, info->Attacker.direction);
//    lua_settable(L, -3);
//    lua_pushstring(L, "MaxHealth");
//    lua_pushnumber(L, info->Attacker.MaxHealth);
//    lua_settable(L, -3);
//    lua_pushstring(L, "Armor");
//    lua_pushnumber(L, info->Attacker.Armor);
//    lua_settable(L, -3);
//    // 继续为 Attacker 的其他字段设置值...
//
//    // 将 Attacker 表插入到 DamageCalcuteInfo 表中
//    lua_setfield(L, -2, "Attacker");
//
//    // 创建 Defender 表
//    lua_newtable(L);
//    lua_pushstring(L, "id");
//    lua_pushnumber(L, info->Defender.id);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_x");
//    lua_pushnumber(L, info->Defender.position_x);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_y");
//    lua_pushnumber(L, info->Defender.position_y);
//    lua_settable(L, -3);
//    lua_pushstring(L, "position_height");
//    lua_pushnumber(L, info->Defender.position_height);
//    lua_settable(L, -3);
//    lua_pushstring(L, "direction");
//    lua_pushnumber(L, info->Defender.direction);
//    lua_settable(L, -3);
//    lua_pushstring(L, "MaxHealth");
//    lua_pushnumber(L, info->Defender.MaxHealth);
//    lua_settable(L, -3);
//    // 继续为 Defender 的其他字段设置值...
//
//    // 将 Defender 表插入到 DamageCalcuteInfo 表中
//    lua_setfield(L, -2, "Defender");
//
//    // 创建 SpatialRelationship 表
//    lua_newtable(L);
//    lua_pushstring(L, "inSight");
//    lua_pushboolean(L, info->Relative.inSight);
//    lua_settable(L, -3);
//    lua_pushstring(L, "inAttackRange");
//    lua_pushboolean(L, info->Relative.inAttackRange);
//    lua_settable(L, -3);
//    lua_pushstring(L, "isBackStrike");
//    lua_pushboolean(L, info->Relative.isBackStrike);
//    lua_settable(L, -3);
//    lua_pushstring(L, "isSideStrike");
//    lua_pushboolean(L, info->Relative.isSideStrike);
//    lua_settable(L, -3);
//
//    // 将 SpatialRelationship 表插入到 DamageCalcuteInfo 表中
//    lua_setfield(L, -2, "Relative");
//};
//
//inline void print_table(lua_State* L, int index, int depth) {
//    lua_pushnil(L);  // 将表中的第一个元素压栈
//    while (lua_next(L, index) != 0) {
//        // 打印缩进（根据深度）
//        for (int i = 0; i < depth; ++i) {
//            std::cout << "  ";  // 用于视觉缩进
//        }
//
//        // 输出键
//        int t = lua_type(L, -2);
//        if (t == LUA_TSTRING) {
//            std::cout << "Key: " << lua_tostring(L, -2) << " -> ";
//        }
//        else {
//            std::cout << "Key (non-string) -> ";
//        }
//
//        // 输出值
//        t = lua_type(L, -1);
//        switch (t) {
//        case LUA_TSTRING:
//            std::cout << "(string) " << lua_tostring(L, -1) << std::endl;
//            break;
//        case LUA_TBOOLEAN:
//            std::cout << "(boolean) " << (lua_toboolean(L, -1) ? "true" : "false") << std::endl;
//            break;
//        case LUA_TNUMBER:
//            std::cout << "(number) " << lua_tonumber(L, -1) << std::endl;
//            break;
//        case LUA_TTABLE:
//            std::cout << "(table) {" << std::endl;
//            // 递归调用，增加深度
//            print_table(L, lua_gettop(L), depth + 1);
//            for (int i = 0; i < depth; ++i) {
//                std::cout << "  ";  // 用于结束递归的缩进
//            }
//            std::cout << "}" << std::endl;
//            break;
//        default:
//            std::cout << "(unknown type)" << std::endl;
//            break;
//        }
//
//        lua_pop(L, 1);  // 弹出当前值，继续下一个键
//    }
//}
//inline void print_stack_frist(lua_State* L)
//{
//    int type = lua_type(L, -1);
//    switch (type) {
//    case LUA_TNIL:
//        std::cout << "Type: NIL" << std::endl;
//        break;
//    case LUA_TBOOLEAN:
//        std::cout << "Type: BOOLEAN, Value: " << (lua_toboolean(L, -1) ? "true" : "false") << std::endl;
//        break;
//    case LUA_TNUMBER:
//        std::cout << "Type: NUMBER, Value: " << lua_tonumber(L, -1) << std::endl;
//        break;
//    case LUA_TSTRING:
//        std::cout << "Type: STRING, Value: " << lua_tostring(L, -1) << std::endl;
//        break;
//    case LUA_TTABLE:
//        std::cout << "Type: TABLE" << std::endl;
//        lua_pushnil(L);  // 将表的第一个键推入栈
//        while (lua_next(L, -2) != 0) {
//            // 打印键值对
//            std::cout << "  Key: " << lua_tostring(L, -2) << " -> " << lua_tointeger(L, -1) << std::endl;
//            lua_pop(L, 1);  // 弹出值，继续遍历
//        }
//        break;
//    case LUA_TFUNCTION:
//        std::cout << "Type: FUNCTION" << std::endl;
//        lua_Debug ar;
//        if (lua_getinfo(L, ">n", &ar)) {
//            // 打印函数的名字（如果有的话）
//            if (ar.name) {
//                std::cout << "Function name: " << ar.name << std::endl;
//            }
//            else {
//                std::cout << "Anonymous function or no name available" << std::endl;
//            }
//        }
//        break;
//    case LUA_TUSERDATA:
//        std::cout << "Type: USERDATA" << std::endl;
//        break;
//    default:
//        std::cout << "Type: UNKNOWN" << std::endl;
//        break;
//    }
//}
//inline void print_lua_stack(lua_State* L) {
//    int stackTop = lua_gettop(L);  // 获取栈顶的索引
//    for (int i = 1; i <= stackTop; ++i) {
//        int t = lua_type(L, i);
//        switch (t) {
//        case LUA_TSTRING:  // 字符串
//            std::cout << "Stack[" << i << "]: (string) " << lua_tostring(L, i) << std::endl;
//            break;
//        case LUA_TBOOLEAN:  // 布尔值
//            std::cout << "Stack[" << i << "]: (boolean) " << (lua_toboolean(L, i) ? "true" : "false") << std::endl;
//            break;
//        case LUA_TNUMBER:  // 数字
//            std::cout << "Stack[" << i << "]: (number) " << lua_tonumber(L, i) << std::endl;
//            break;
//        case LUA_TTABLE:  // 表
//            std::cout << "Stack[" << i << "]: (table) {" << std::endl;
//            print_table(L, i, 1);  // 调用递归打印函数，初始深度为1
//            std::cout << "}" << std::endl;
//            break;
//        default:
//            std::cout << "Stack[" << i << "]: (unknown type)" << std::endl;
//            break;
//        }
//    }
//}
//
//void register_lua_function(lua_State* L, const std::string& func_name) {
//    // 确保 Lua 解释器已初始化
//    if (!L) {
//        std::cerr << "Lua interpreter is not initialized!" << std::endl;
//        return;
//    }
//
//    // 获取 Lua 函数
//    lua_getglobal(L, func_name.c_str());
//    if (lua_isfunction(L, -1)) {
//        // 将 Lua 函数包装为 C++ 函数
//        A1_dynamic = [L, func_name](int x) {
//            // 将参数压栈
//            lua_pushnumber(L, x);
//
//            // 调用 Lua 函数
//            if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
//                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
//                lua_pop(L, 1);  // 错误处理
//            }
//            };
//
//        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
//    }
//    else {
//        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
//    }
//
//    // 清理栈
//    lua_pop(L, 1);
//}
//
// // register.lua 
// function WaterBall(info)
//print_table(info)
//--获取 Attacker 表
//local attacker = info["Attacker"]
//
//--检查 attacker 是否为 nil
//if attacker == nil then
//print("Error: Attacker is nil!")
//return 0  --或者返回一个默认值
//end
//
//-- 检查 Armor 是否存在
//local armor = attacker["Armor"]
//if armor == nil then
//print("Error: Armor is nil in Attacker!")
//return 0  --或者返回一个默认值
//end
//
//-- 返回 Attacker.Armor * 30 + 50
//return armor * 30 + 50
//end

//void Register_lua(lua_State* L, int64_t id, const std::string& script_name, const std::string& func_name) {
//    if (!L) {
//        std::cerr << "Lua interpreter is not initialized!" << std::endl;
//        return;
//    }
//
//    // 加载 Lua 脚本
//    if (luaL_dofile(L, script_name.c_str()) != LUA_OK) {
//        std::cerr << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
//        lua_pop(L, 1);  // 弹出错误信息
//        return;
//    }
//
//    // 获取 Lua 函数
//    lua_getglobal(L, func_name.c_str());  // 获取 Lua 中定义的函数
//
//    // 检查栈顶是否是一个有效的函数
//    if (lua_isfunction(L, -1)) {
//        // 将 Lua 函数和 id 存储到 SkillMap 中
//        SkillMap[id] = [L, func_name](DamageCalcuteInfo* info) -> double {
//            // 将 DamageCalcuteInfo 转换并推送到 Lua 栈
//            push_damage_info_to_lua(L, info);  // 将信息推送到栈
//
//            // 调用 Lua 函数
//            if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
//                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
//                lua_pop(L, 1);  // 弹出错误信息
//                return 0.0;  // 如果出错，返回默认值
//            }
//
//            // 获取 Lua 函数的返回值（假设它是一个数字）
//            double result = 0.0;
//            if (lua_isnumber(L, -1)) {
//                result = lua_tonumber(L, -1);  // 获取返回的数字值
//            }
//            else {
//                std::cerr << "Lua function did not return a number!" << std::endl;
//            }
//
//            // 清理 Lua 栈
//            lua_pop(L, 1);  // 弹出返回值
//            return result;
//            };
//
//        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
//    }
//    else {
//        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
//    }
//
//    // 弹出函数引用，清理栈
//    lua_pop(L, 1);
//}


//if (command == "testlua")
//{
//    testLua();
//    return;
//}
//if (command == "reglua")
//{
//    sol::state lua;
//    lua.open_libraries(sol::lib::base);  // 打开基本库
//    lua.set_function("add", add);  // 将 C++ 函数 add 注册到 Lua 中
//    // 运行 Lua 脚本，替换 add 函数
//    runLuaFromFile(lua, "add.lua");
//    sol::protected_function_result ret = lua["add"](3, 4);
//    // 调用 Lua 中的 add 函数
//    std::cout << "Result of add(3, 4): " << ret.begin()->as<int>() << std::endl;  // 输出 12（3 * 4）
//    return;
//}
