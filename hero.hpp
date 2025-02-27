class hero : public entity, public sf::RectangleShape
{
private:
    float *supplies_level;
    float *points;
    float *velocity_x;
    float *velocity_y;
    int *animation_state;
    float *acceleration_y;
    float *previous_x;
    float *previous_y;
    bool *is_jumping;
    float *supply_drop_rate;
    sf::SoundBuffer *buffer_0;//wszystkie dźwięki w grze
    sf::Sound *sound_0;
    sf::SoundBuffer *buffer_1;
    sf::Sound *sound_1;
    sf::SoundBuffer *buffer_2;
    sf::Sound *sound_2;
    sf::Texture *texture_0;

public:
    void update(float *time_elapsed, std::vector<entity *> *all_objects);
    void update_positions(float *time_elapsed);
    void update_supplies(float *time_elapsed);
    void update_velocity(float *time_elapsed);
    void update_animation();
    void decollide(std::vector<entity *> *all_objects);
    void collide(std::vector<entity *> *all_objects);
    void set_supply_drop_rate(float *supply_drop_rate_arg);
    float *get_points();
    float *get_supplies_level();
    hero();
    ~hero();
    void set_jump();
};