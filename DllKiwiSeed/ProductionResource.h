#pragma once
#include <vector>
#include <map>
#ifndef ProductionResource_H
#define ProductionResource_H

#ifdef ProductionResource_EXPORTS
#define ProductionResource_API __declspec(dllexport)
#define ProductionResourceManager_API __declspec(dllexport)
#else
#define ProductionResource_API __declspec(dllimport)
#define ProductionResourceManager_API __declspec(dllimport)
#endif

class ProductionResourceManager_API ProductionResourceManager {
public:
    ProductionResourceManager();
    ~ProductionResourceManager();
    void AddResource();
    void RemoveResource();
    bool IsQualified(std::map<uint64_t, uint64_t> cost);
    void Cost(std::map<uint64_t, uint64_t> cost);
    ProductionResource* GetResource();
private:
    std::vector<ProductionResource*> m_resources;
};


class ProductionResource_API ProductionResource {
public:
    ProductionResource();
    ~ProductionResource();
    void SetQuality(uint64_t quality);
    uint64_t GetQuality();
    uint64_t GetResourceId();
    uint64_t GetAdjQuality();
    bool IsQualified(uint64_t q);
    void Cost(uint64_t q);
private:
    uint64_t quality;
    uint64_t resource_id;
    std::map<uint64_t, uint64_t> adj;
};

#endif
