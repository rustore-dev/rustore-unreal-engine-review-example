## RuStore Unreal Engine плагин для оценок и отзывов

### [🔗 Документация разработчика](https://help.rustore.ru/rustore/for_developers/developer-documentation/SDK-reviews-ratings/unreal)

Плагин RuStoreReview позволяет пользователю оставить оценку и отзыв о вашем приложении в RuStore, не выходя из приложения. 

Репозиторий содержит плагины “RuStoreReview” и “RuStoreCore”, а также демонстрационное приложение с примерами использования и настроек. Поддерживаются версии UE 4.26 и выше.


### Установка плагина в свой проект

1. Скопируйте содержимое папки _“Plugins”_ в папку _“Plugins”_ внутри своего проекта. Перезапустите Unreal Engine, в списке плагинов (Edit → Plugins → Project → Mobile) отметьте плагины “RuStoreReview” и “RuStoreCore”.

2. В файле _“YourProject.Build.cs”_ в списке PublicDependencyModuleNames подключите модули модули “RuStoreCore” и “RuStoreReview”.

3. В настройках проекта (Edit → Project Settings → Android) установить параметр Minimum SDK Version на уровень не ниже 24 и параметр Target SDK Version - не ниже 31.


### Сборка примера приложения

1. В настройках проекта (Edit → Project Settings → Platforms → Android) укажите имя пакета “Android Package Name” и параметры подписи “Distribution Signing” вашего приложения в RuStore. Подробная информация о публикации приложений в RuStore доступна на странице [help](https://help.rustore.ru/rustore/for_developers/publishing_and_verifying_apps).


### Техническая поддержка

Дополнительная помощь и инструкции доступны на странице [help.rustore.ru](https://help.rustore.ru/).
