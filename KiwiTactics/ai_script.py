#def run_ai():
#    # 创建一个角色实例
#    print(1+1)
# 调用 AI 控制逻辑
#run_ai()
import ai_module

# 创建 C++ 类的实例
model = ai_module.AIModel("TestModel")
model.train()

# 使用 C++ 类的成员方法
result = model.predict("sample input")
print(result)
