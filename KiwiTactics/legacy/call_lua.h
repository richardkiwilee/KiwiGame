//#include <iostream>
//#include <sol/sol.hpp>  // ���� sol2 ��
//
//// ���� C++ ��
//class AIModel_Lua {
//public:
//    std::string model_name;
//    int a;  // ������ public ��Ա
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
//    -- �޸� C++ �����Ա���� a
//    model.a = 42
//
//    print("After modification: " .. model.a)
//    */
//    sol::state lua;
//    lua.open_libraries(sol::lib::base, sol::lib::package);
//    // �� C++ ���󴫵ݸ� Lua
//    lua.set("model", &model);
//    // ע�� AIModel_Lua ���͵� Lua��ʹ�� Lua ������ȷ���� C++ ��
//    lua.new_usertype<AIModel_Lua>("AIModel_Lua",
//        "train", &AIModel_Lua::train,
//        "predict", &AIModel_Lua::predict,
//        "a", &AIModel_Lua::a,  // ��¶��Ա����
//        "model_name", &AIModel_Lua::model_name  // ��¶��Ա����
//    );
//    // ִ�� Lua �ű�
//    try {
//        lua.script_file(script);
//        // �ڽű�ִ�к���� C++ �����Ա���� a ��ֵ
//        std::cout << "C++ value of 'a' after Lua modification: " << model.a << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error running Lua script: " << e.what() << std::endl;
//    }
//}
//
//int testLua() {
//    // ���� C++ ����ʵ��
//    AIModel_Lua model("AI Model", 10);
//    // ����޸�ǰ�� 'a'
//    std::cout << "Initial value of 'a' in C++: " << model.a << std::endl;
//    // ���� Lua �ű������ݶ���
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
//        lua.script_file(filename);  // ִ�� Lua �ļ�
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
//    lua_newtable(L);  // ���� Attacker ��
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
//    lua_settable(L, -3);  // �� Attacker ����� DamageCalcuteInfo ��
//    std::cout << "Pushed " << name << " to DamageCalcuteInfo table" << std::endl;
//
//}
//inline void push_SpatialRelationship_to_lua(lua_State* L, SpatialRelationship* info, std::string name)
//{
//    // �� Relative ת��Ϊ Lua ��
//    lua_pushstring(L, name.c_str());
//    lua_newtable(L);  // ���� Relative ��
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
//    // ����һ���µı�����ʾ DamageCalcuteInfo
//    lua_newtable(L);
//    push_CharacterInfo_to_lua(L, &info->Attacker, "Attacker");
//    push_CharacterInfo_to_lua(L, &info->Defender, "Defender");
//    push_SpatialRelationship_to_lua(L, &info->Relative, "Relative");
//    // lua_settable(L, -1);    // Lua after push info: 1
//    // lua_settable(L, -2);    // crash
//    lua_settable(L, -3);    // Lua after push info: 1 ջ��table
//    // lua_settable(L, -4);    // crash
//}
//inline void push_damage_info_to_lua(lua_State* L, DamageCalcuteInfo* info) {
//    // ���� DamageCalcuteInfo ��
//    lua_newtable(L);
//
//    // ���� Attacker ��
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
//    // ����Ϊ Attacker �������ֶ�����ֵ...
//
//    // �� Attacker ����뵽 DamageCalcuteInfo ����
//    lua_setfield(L, -2, "Attacker");
//
//    // ���� Defender ��
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
//    // ����Ϊ Defender �������ֶ�����ֵ...
//
//    // �� Defender ����뵽 DamageCalcuteInfo ����
//    lua_setfield(L, -2, "Defender");
//
//    // ���� SpatialRelationship ��
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
//    // �� SpatialRelationship ����뵽 DamageCalcuteInfo ����
//    lua_setfield(L, -2, "Relative");
//};
//
//inline void print_table(lua_State* L, int index, int depth) {
//    lua_pushnil(L);  // �����еĵ�һ��Ԫ��ѹջ
//    while (lua_next(L, index) != 0) {
//        // ��ӡ������������ȣ�
//        for (int i = 0; i < depth; ++i) {
//            std::cout << "  ";  // �����Ӿ�����
//        }
//
//        // �����
//        int t = lua_type(L, -2);
//        if (t == LUA_TSTRING) {
//            std::cout << "Key: " << lua_tostring(L, -2) << " -> ";
//        }
//        else {
//            std::cout << "Key (non-string) -> ";
//        }
//
//        // ���ֵ
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
//            // �ݹ���ã��������
//            print_table(L, lua_gettop(L), depth + 1);
//            for (int i = 0; i < depth; ++i) {
//                std::cout << "  ";  // ���ڽ����ݹ������
//            }
//            std::cout << "}" << std::endl;
//            break;
//        default:
//            std::cout << "(unknown type)" << std::endl;
//            break;
//        }
//
//        lua_pop(L, 1);  // ������ǰֵ��������һ����
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
//        lua_pushnil(L);  // ����ĵ�һ��������ջ
//        while (lua_next(L, -2) != 0) {
//            // ��ӡ��ֵ��
//            std::cout << "  Key: " << lua_tostring(L, -2) << " -> " << lua_tointeger(L, -1) << std::endl;
//            lua_pop(L, 1);  // ����ֵ����������
//        }
//        break;
//    case LUA_TFUNCTION:
//        std::cout << "Type: FUNCTION" << std::endl;
//        lua_Debug ar;
//        if (lua_getinfo(L, ">n", &ar)) {
//            // ��ӡ���������֣�����еĻ���
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
//    int stackTop = lua_gettop(L);  // ��ȡջ��������
//    for (int i = 1; i <= stackTop; ++i) {
//        int t = lua_type(L, i);
//        switch (t) {
//        case LUA_TSTRING:  // �ַ���
//            std::cout << "Stack[" << i << "]: (string) " << lua_tostring(L, i) << std::endl;
//            break;
//        case LUA_TBOOLEAN:  // ����ֵ
//            std::cout << "Stack[" << i << "]: (boolean) " << (lua_toboolean(L, i) ? "true" : "false") << std::endl;
//            break;
//        case LUA_TNUMBER:  // ����
//            std::cout << "Stack[" << i << "]: (number) " << lua_tonumber(L, i) << std::endl;
//            break;
//        case LUA_TTABLE:  // ��
//            std::cout << "Stack[" << i << "]: (table) {" << std::endl;
//            print_table(L, i, 1);  // ���õݹ��ӡ��������ʼ���Ϊ1
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
//    // ȷ�� Lua �������ѳ�ʼ��
//    if (!L) {
//        std::cerr << "Lua interpreter is not initialized!" << std::endl;
//        return;
//    }
//
//    // ��ȡ Lua ����
//    lua_getglobal(L, func_name.c_str());
//    if (lua_isfunction(L, -1)) {
//        // �� Lua ������װΪ C++ ����
//        A1_dynamic = [L, func_name](int x) {
//            // ������ѹջ
//            lua_pushnumber(L, x);
//
//            // ���� Lua ����
//            if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
//                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
//                lua_pop(L, 1);  // ������
//            }
//            };
//
//        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
//    }
//    else {
//        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
//    }
//
//    // ����ջ
//    lua_pop(L, 1);
//}
//
// // register.lua 
// function WaterBall(info)
//print_table(info)
//--��ȡ Attacker ��
//local attacker = info["Attacker"]
//
//--��� attacker �Ƿ�Ϊ nil
//if attacker == nil then
//print("Error: Attacker is nil!")
//return 0  --���߷���һ��Ĭ��ֵ
//end
//
//-- ��� Armor �Ƿ����
//local armor = attacker["Armor"]
//if armor == nil then
//print("Error: Armor is nil in Attacker!")
//return 0  --���߷���һ��Ĭ��ֵ
//end
//
//-- ���� Attacker.Armor * 30 + 50
//return armor * 30 + 50
//end

//void Register_lua(lua_State* L, int64_t id, const std::string& script_name, const std::string& func_name) {
//    if (!L) {
//        std::cerr << "Lua interpreter is not initialized!" << std::endl;
//        return;
//    }
//
//    // ���� Lua �ű�
//    if (luaL_dofile(L, script_name.c_str()) != LUA_OK) {
//        std::cerr << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
//        lua_pop(L, 1);  // ����������Ϣ
//        return;
//    }
//
//    // ��ȡ Lua ����
//    lua_getglobal(L, func_name.c_str());  // ��ȡ Lua �ж���ĺ���
//
//    // ���ջ���Ƿ���һ����Ч�ĺ���
//    if (lua_isfunction(L, -1)) {
//        // �� Lua ������ id �洢�� SkillMap ��
//        SkillMap[id] = [L, func_name](DamageCalcuteInfo* info) -> double {
//            // �� DamageCalcuteInfo ת�������͵� Lua ջ
//            push_damage_info_to_lua(L, info);  // ����Ϣ���͵�ջ
//
//            // ���� Lua ����
//            if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
//                std::cerr << "Error calling Lua function: " << lua_tostring(L, -1) << std::endl;
//                lua_pop(L, 1);  // ����������Ϣ
//                return 0.0;  // �����������Ĭ��ֵ
//            }
//
//            // ��ȡ Lua �����ķ���ֵ����������һ�����֣�
//            double result = 0.0;
//            if (lua_isnumber(L, -1)) {
//                result = lua_tonumber(L, -1);  // ��ȡ���ص�����ֵ
//            }
//            else {
//                std::cerr << "Lua function did not return a number!" << std::endl;
//            }
//
//            // ���� Lua ջ
//            lua_pop(L, 1);  // ��������ֵ
//            return result;
//            };
//
//        std::cout << "Lua function " << func_name << " registered successfully!" << std::endl;
//    }
//    else {
//        std::cerr << "Function " << func_name << " not found or not callable in Lua" << std::endl;
//    }
//
//    // �����������ã�����ջ
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
//    lua.open_libraries(sol::lib::base);  // �򿪻�����
//    lua.set_function("add", add);  // �� C++ ���� add ע�ᵽ Lua ��
//    // ���� Lua �ű����滻 add ����
//    runLuaFromFile(lua, "add.lua");
//    sol::protected_function_result ret = lua["add"](3, 4);
//    // ���� Lua �е� add ����
//    std::cout << "Result of add(3, 4): " << ret.begin()->as<int>() << std::endl;  // ��� 12��3 * 4��
//    return;
//}
