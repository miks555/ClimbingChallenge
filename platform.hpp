class platform : public entity, public sf::RectangleShape
{
public:
    platform(float x, float y);
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
};