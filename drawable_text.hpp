class drawable_text : public entity, public sf::Text
{
public:
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
    drawable_text();
    ~drawable_text();

private:
    sf::Font *font_0;
};
