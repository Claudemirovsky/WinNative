#include <jni.h>
#include <stdint.h>

// FEX-Emu accumulates JIT/signal time in the shm stats as CNTVCT_EL0 cycles, so
// the HUD needs the CNTFRQ_EL0 frequency to turn cycle deltas into load
// percentages.
JNIEXPORT jlong JNICALL
Java_com_winlator_cmod_runtime_display_ui_FexStats_nativeCycleCounterFrequency(
    JNIEnv *env, jclass clazz) {
    (void)env;
    (void)clazz;
#if defined(__aarch64__)
    uint64_t freq = 0;
    __asm__ volatile("mrs %0, CNTFRQ_EL0" : "=r"(freq));
    return (jlong)freq;
#else
    return 0;
#endif
}
