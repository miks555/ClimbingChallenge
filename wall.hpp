class wall : public entity, public sf::RectangleShape
{
public:
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
    wall();
};