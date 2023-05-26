#include "window.h"
#include <iostream>
#include <locale.h>

Window::Window()
{
    setup("Window", sf::Vector2u(512,512));

}

Window::Window(const std::string& title,const sf::Vector2u& size)
{
    setup(title, size);
}
Window::~Window()
{
    destroy();
}
std::string Window::get_window_title() const
{
    return window_title;
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
    setlocale(LC_CTYPE, "Polish");
    this->comic_sans.loadFromFile("src/fonts/ComicSansMS3.ttf");
    this->window_title = title;
    this->window_size = size;
    this->is_done = false;
    this->is_fullscreen = false;
    this->in_lobby = true;
    render_window.setFramerateLimit(60);
    create();
}
void Window::destroy()
{
    render_window.close();
}
void Window::create()
{
    auto style = (is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    render_window.create({ window_size.x, window_size.y, 32 }, window_title, style);
}

bool Window::get_is_done() const
{
    return is_done;
}
bool Window::get_is_fullscreen() const
{
    return is_fullscreen;
}
sf::Vector2u Window::get_window_size() const
{
    return window_size;
}
void Window::begin_draw(sf::Color color) // Clears the window
{
    render_window.clear(color);
}
void Window::end_draw() //Shows result
{
    render_window.display();
}
void Window::update()
{
    sf::Event event;
    while(render_window.pollEvent(event)){
    if(event.type == sf::Event::Closed){
        is_done = true;
        //std::cout<<"ZAMKNIETO OKNO!\n";
    }
    else if(event.type == sf::Event::KeyPressed &&
    event.key.code == sf::Keyboard::F5)
    {
        toggle_fullscreen();
    }
    }
}
void Window::toggle_fullscreen()
{
    is_fullscreen = !is_fullscreen;
    destroy();
    create();
}
void Window::draw(const sf::Drawable& drawable)
{
    render_window.draw(drawable);
}

void Window::draw_tile_collection(const TileManager& tile_manager, int current_ferdek_column)
{
    int x = tile_manager.GetTiles().size();
    int y = tile_manager.GetTiles()[0].size();
    for(int i=std::max(0, current_ferdek_column-32);i<std::min(32+current_ferdek_column, x);i++)
    {
        for(int j=0;j<y;j++)
        {
            if(tile_manager.CheckTile(i, j)){
                draw(tile_manager.GetTiles()[i][j]->get_sprite());

            }
        }
    }
}


void Window::update_view(const float& player_x, const float& min_x, const float& max_x)
{
    float top_x = std::max(min_x, player_x-window_size.x/2);
    top_x = std::min(top_x, max_x-window_size.x);
    sf::View view(sf::FloatRect(top_x, 0.f, window_size.x, window_size.y));
    render_window.setView(view);
}

sf::Vector2u Window::get_actual_size() const
{
    return render_window.getSize();
}

void Window::draw_mobs(const std::vector<std::shared_ptr<Mob>>& mobs, float ferdek_position_x)
{
    int n = mobs.size();
    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek_position_x-mobs[i]->GetPosition().x)/32 < 24)
        {
            draw(mobs[i]->GetSprite());

        }
    }
}

void Window::draw_stats(const unsigned int& coins, const int& lives, const int& level, const float& player_x, const float& min_x, const float& max_x)
{
    float top_x = std::max(min_x, player_x-window_size.x/2);
    top_x = std::min(top_x, max_x-window_size.x);
    sf::Vector2f position(top_x, 0);
    std::wstring content = L" zł";
    content = std::to_wstring(coins)+content;
    sf::Text result_text (content, comic_sans);
    result_text.setCharacterSize(64);
    result_text.setFillColor(sf::Color(255, 255, 0));
    result_text.setPosition(position);
    draw(result_text);

    content = L"Życia: ";
    content = content + std::to_wstring(lives);
    result_text.setCharacterSize(64);
    result_text.setFillColor(sf::Color::Red);
    result_text.setPosition(position); 
    result_text.setString(content);
    position.x += window_size.x * 0.25f;
    result_text.setPosition(position);
    draw(result_text);  
    content = L"Poziom: ";
    content = content + std::to_wstring(level);
    result_text.setCharacterSize(64);
    result_text.setFillColor(sf::Color::Black);
    position.x += window_size.x * 0.25f;
    result_text.setPosition(position); 
    result_text.setString(content);
    draw(result_text);

}

void Window::start_window()
{
    this->in_lobby = true;
    
    sf::RectangleShape startButton(sf::Vector2f(400, 100));
    startButton.setPosition(300, 250);
    startButton.setFillColor(sf::Color::Green);

    update_view(0,0,10000);
    sf::Text buttonText("START - kliknij enter", comic_sans, 30);
    buttonText.setPosition(360, 280);
    buttonText.setFillColor(sf::Color::White);

    sf::Text Title("SUPER FERDEK", comic_sans, 60);
    Title.setPosition(360, 80);
    Title.setFillColor(sf::Color::Black);

    //render_window.display();
    while(true)
    {
        begin_draw();
        draw(startButton);
        draw(buttonText);
        draw(Title);
        sf::Event event;
        while(render_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            is_done = true;
            return;
            //std::cout<<"ZAMKNIETO OKNO!\n";
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::F5)
        {
            toggle_fullscreen();
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter)
        {
            this->in_lobby = false;
            return;
        }
        }
        end_draw();
    }
}

void Window::end_window_after_lost()
{
    this->in_lobby = true;
    
    sf::RectangleShape startButton(sf::Vector2f(400, 100));
    startButton.setPosition(300, 250);
    startButton.setFillColor(sf::Color::Red);

    update_view(0,0,10000);
    sf::Text buttonText("MENU - kliknij enter", comic_sans, 20);
    buttonText.setPosition(360, 280);
    buttonText.setFillColor(sf::Color::White);

    sf::Text Title("Przegrana", comic_sans, 60);
    Title.setPosition(360, 80);
    Title.setFillColor(sf::Color::Red);

    //render_window.display();
    while(true)
    {
        begin_draw(sf::Color::Black);
        draw(startButton);
        draw(buttonText);
        draw(Title);
        sf::Event event;
        while(render_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            is_done = true;
            return;
            //std::cout<<"ZAMKNIETO OKNO!\n";
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::F5)
        {
            toggle_fullscreen();
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter)
        {
            this->in_lobby = false;
            return;
        }
        }
        end_draw();
    }
}

void Window::end_window_after_win(const unsigned int& result)
{
    this->in_lobby = true;
    
    sf::RectangleShape startButton(sf::Vector2f(400, 100));
    startButton.setPosition(300, 250);
    startButton.setFillColor(sf::Color::Black);

    update_view(0,0,10000);
    sf::Text buttonText("MENU - kliknij enter", comic_sans, 20);
    buttonText.setPosition(360, 280);
    buttonText.setFillColor(sf::Color::White);

    sf::Text Title("WYGRANA", comic_sans, 60);
    Title.setPosition(360, 80);
    Title.setFillColor(sf::Color::Black);
    sf::Text result_text(std::to_wstring(result)+L"zł", comic_sans, 60);
    result_text.setPosition(360, 120);
    result_text.setFillColor(sf::Color::Black);
    //render_window.display();
    while(true)
    {
        begin_draw(sf::Color::Yellow);
        draw(startButton);
        draw(buttonText);
        draw(Title);
        draw(result_text);
        sf::Event event;
        while(render_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            is_done = true;
            return;
            //std::cout<<"ZAMKNIETO OKNO!\n";
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::F5)
        {
            toggle_fullscreen();
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter)
        {
            this->in_lobby = false;
            return;
        }
        }
        end_draw();
    }
}
void Window::draw_ferdek(Ferdek& ferdek)
{
    ferdek.set_sprite_origin(0, 32+16*ferdek.get_is_big());
    draw(ferdek.get_sprite());
}