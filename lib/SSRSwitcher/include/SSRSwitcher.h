/**
 * @file SSRSwitcher.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief includes all method's possible for SSRSwitcher
 *
 * Copyright (c) Nebensound GmbH 2022
 *
 */
#pragma once

namespace SSRSwitcher
{
    typedef enum
    {
        Ok,
    } ErrorCode;

    typedef enum
    {
        open,
        closed,
        shutoff,
        waiting,
        testing
    } OutputStatus;

    /**
     * @brief sets up the SSRSwitcher
     *
     * @param interval the interval the libary will check if the status has changed and take action in ms
     */
    void setup(unsigned int interval);
} // namespace SSRSwitcher
