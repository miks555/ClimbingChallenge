class rock : public entity, public sf::RectangleShape
{
private:
    float *animation_time;
    int *animation_state;

public:
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
    rock(float x, float y);
    ~rock();
};