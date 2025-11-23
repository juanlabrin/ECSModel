#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using Entity = std::uint32_t;

class Registry {
    public:
    Entity createEntity() {
        Entity id = nextId++;
        entities.push_back(id);
        return id;
    }

    template <typename T>
    void add(Entity e, const T& component) {
        auto& pool = poolOf<T>();
        pool[e] = component;
    }

    template <typename T>
    bool has(Entity e) {
        auto& pool = poolOf<T>();
        return pool.contains(e);
    }

    template <typename T>
    T& get(Entity e) {
        return poolOf<T>().at[e];
    }

    template <typename... Components, typename Func>
    void view(Func f) {
        for (Entity e : entities) {
            if ((has<Components>(e) && ...)) {
                f(e, get<Components>(e)...);
            }
        }
    }
private:
    Entity nextId = 1;
    std::vector<Entity> entities;

    template <typename T>
    std::unordered_map<Entity, T>& poolOf() {
        static std::unordered_map<Entity, T> pool;
        return pool;
    }
};

int main() {
    return 0;
}