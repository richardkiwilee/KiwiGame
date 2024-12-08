#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger {
public:
    // 获取单例实例
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    };

    // 禁止拷贝构造和赋值操作符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void Info(const std::string& msg) {
        console->info(msg);
        file_logger->info(msg);
    }

    void Warn(const std::string& msg) {
		console->warn(msg);
		file_logger->warn(msg);
	}

    void Error(const std::string& msg) {
        console->error(msg);
        file_logger->error(msg);
    }

    void Catch(const std::exception& e)
    {
        //try {
        //    throw std::runtime_error("An example exception");
        //}
        //catch (const std::exception& e) {
        //    spdlog::error("Caught an exception: {}", e.what());
        //}
        spdlog::error("Caught an exception: {}", e.what());
    }

private:
    // 私有构造函数和析构函数
    Logger()
    {
        console = spdlog::stdout_color_mt("console");
        console->set_level(spdlog::level::info); // 设置日志级别
        console->set_pattern("[%Y-%m-%d %H:%M:%S] [%-5l] %v"); // 设置日志格式
        file_logger = spdlog::basic_logger_mt("file_logger", "logs/example.log");
        file_logger->set_level(spdlog::level::debug); // 设置文件日志级别
        file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // 设置日志格式
    };
    ~Logger() {};

    std::shared_ptr<spdlog::logger> console = nullptr;
    std::shared_ptr<spdlog::logger> file_logger = nullptr;

};

#endif
