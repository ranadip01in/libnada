#pragma once

namespace nada::time {

    /** 
     * Gives you the amount of milliseconds from a fixed point in time. 
     * Does roughly the same as you'd expect from Java's `System.currentTimeMillis()`.
     */
    unsigned long long millis();

    /** 
     * Let the executing thread sleep for `millis` milliseconds.
     * @param millis Milliseconds to sleep.
     */ 
    void sleep(unsigned millis);

}