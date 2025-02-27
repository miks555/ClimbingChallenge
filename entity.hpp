class entity
{
public:
    virtual void update(float *time_elapsed, std::vector<entity *> *all_objects) = 0;
    virtual ~entity() = default;
};