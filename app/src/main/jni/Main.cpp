#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <unistd.h>

// Определяем тег для логов
#define LOG_TAG "AmonixMod"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Функция для инициализации в отдельном потоке (чтобы не вешать игру)
void* init_thread(void* arg) {
    // Ждем немного перед логированием, чтобы игра успела прогрузить базовые процессы
    sleep(5); 
    
    LOGI("======================================");
    LOGI("AmonixMod: Поток запущен успешно!");
    LOGI("======================================");
    
    return nullptr;
}

// Главная точка входа (JNI_OnLoad)
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t thread;
    // Создаем отдельный поток для работы, чтобы не блокировать основной поток игры
    if (pthread_create(&thread, nullptr, init_thread, nullptr) != 0) {
        LOGI("AmonixMod: Ошибка при создании потока!");
        return JNI_ERR;
    }
    
    LOGI("AmonixMod: Библиотека загружена, поток инициализации создан.");
    
    return JNI_VERSION_1_6;
}
