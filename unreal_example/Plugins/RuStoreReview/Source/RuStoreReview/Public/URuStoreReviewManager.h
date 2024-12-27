// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "URuStoreReviewManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestReviewFlowResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLaunchReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLaunchReviewFlowResponseDelegate, int64, requestId);

using namespace RuStoreSDK;

/*!
@brief
    Класс для работы с оценками и отзывами.
    Предоставляет API для запуска UI-формы, позволяющей пользователю оставить оценку и отзыв о вашем приложении в "RuStore".
*/
UCLASS(Blueprintable)
class RUSTOREREVIEW_API URuStoreReviewManager : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreReviewManager* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

public:
    /*!
    @brief Версия плагина.
    */
    static const FString PluginVersion;

    /*!
    @brief Проверка инициализации менеджера.
    @return Возвращает true, если синглтон инициализирован, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    bool GetIsInitialized();

    /*!
    @brief
        Получить экземпляр URuStoreReviewManager.
    @return
        Возвращает указатель на единственный экземпляр URuStoreReviewManager (реализация паттерна Singleton).
        Если экземпляр еще не создан, создает его.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    static URuStoreReviewManager* Instance();

    /*!
    @brief Обработка ошибок в нативном SDK.
    @param value true — разрешает обработку ошибок, false — запрещает.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void SetAllowNativeErrorHandling(bool value);

    /*!
    @brief Выполняет инициализацию синглтона URuStoreReviewManager.
    @return Возвращает true, если инициализация была успешно выполнена, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    bool Init();

    /*!
    @brief Деинициализация синглтона, если дальнейшая работа с объектом больше не планируется.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void Dispose();

    void ConditionalBeginDestroy();

    /*!
    @brief
        Выполняет подготовку данных для запуска формы оценки и отзыва.
        Метод должен быть вызван перед каждым вызовом LaunchReviewFlow.
        Время жизни подготовленных данных — около пяти минут.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long RequestReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief
        Выполняет запуск формы для запроса оценки и отзыва у пользователя.
        Каждому вызову метода должен предшествовать вызов RequestReviewFlow.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long LaunchReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void RequestReviewFlow(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FRequestReviewFlowErrorDelegate OnRequestReviewFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FRequestReviewFlowResponseDelegate OnRequestReviewFlowResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void LaunchReviewFlow(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FLaunchReviewFlowErrorDelegate OnLaunchReviewFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FLaunchReviewFlowResponseDelegate OnLaunchReviewFlowResponse;
};
