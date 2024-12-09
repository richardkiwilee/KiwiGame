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
        system_file_logger->info(msg);
        system_file_logger->flush();
        if (sav_file_logger != nullptr)
        {
            sav_file_logger->info(msg);
			sav_file_logger->flush();
        }
    }

    void Warn(const std::string& msg) {
		console->warn(msg);
        system_file_logger->warn(msg);
        system_file_logger->flush();
        if (sav_file_logger != nullptr)
        {
            sav_file_logger->warn(msg);
            sav_file_logger->flush();
        }
	}

    void Error(const std::string& msg) {
        console->error(msg);
        system_file_logger->error(msg);
        system_file_logger->flush();
        if (sav_file_logger != nullptr)
        {
            sav_file_logger->error(msg);
            sav_file_logger->flush();
        }
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

    void InitArchiveLogger(std::string name)
    {
        if (sav_file_logger == nullptr)
        {
            sav_file_logger = spdlog::basic_logger_mt("sav_file_logger", "logs/" + name + ".log");
            sav_file_logger->set_level(spdlog::level::debug); // 设置文件日志级别
            sav_file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // 设置日志格式
        }
    };

    void CloseArchiveLogger()
	{
		if (sav_file_logger != nullptr)
		{
			spdlog::drop("sav_file_logger");
			sav_file_logger = nullptr;
		}
	};

private:
    // 私有构造函数和析构函数
    Logger()
    {
        console = spdlog::stdout_color_mt("console");
        console->set_level(spdlog::level::debug); // 设置日志级别
        console->set_pattern("[%Y-%m-%d %H:%M:%S] [%-5l] %v"); // 设置日志格式
        system_file_logger = spdlog::basic_logger_mt("system_file_logger", "logs/system.log");
        system_file_logger->set_level(spdlog::level::debug); // 设置文件日志级别
        system_file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // 设置日志格式
    };
    ~Logger() {};
    std::shared_ptr<spdlog::logger> console = nullptr;
    std::shared_ptr<spdlog::logger> sav_file_logger = nullptr;
    std::shared_ptr<spdlog::logger> system_file_logger = nullptr;

};

#endif
