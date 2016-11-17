#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"

#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <iostream>

void WriteJson()
{
  Json::Value settings;
  Json::Value resolutions(Json::arrayValue);
  resolutions.append(Json::Value("800x600"));
  resolutions.append(Json::Value("1024x768"));
  resolutions.append(Json::Value("1280x1024"));

  auto & root = settings["settings"];
  root["resolution"] = resolutions;
  root["aliensCount"] = 100;
  root["bulletsCount"] = 200;

  root["entities"]["gun"]["health"] = 50;
  root["entities"]["alien"]["health"] = 20;
  root["entities"]["obstacle"]["health"] = 15;

  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}

void ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }

  Json::Value & resolutions = settings["settings"]["resolution"];
  if (resolutions.isArray())
  {
    for (Json::Value::ArrayIndex i = 0; i < resolutions.size(); i++)
      std::cout << resolutions[i].asString() << std::endl;
  }
  std::cout << settings["settings"]["aliensCount"].asInt() << std::endl;
  std::cout << settings["settings"]["bulletsCount"].asInt() << std::endl;

  Json::Value & entities = settings["settings"]["entities"];
  std::cout << entities["gun"]["health"].asInt() << std::endl;
  std::cout << entities["alien"]["health"].asInt() << std::endl;
  std::cout << entities["obstacle"]["health"].asInt() << std::endl;
}

int main(int argc, char ** argv)
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow mw;
  mw.show();
  return a.exec();
}
