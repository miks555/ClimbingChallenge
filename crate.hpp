class crate : public entity, public sf::RectangleShape
{
private:
    float *animation_time;
    bool *animation_state;

public:
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
    crate(float x, float y);
    ~crate();
};