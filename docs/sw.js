/*
 * DNAPass Password Generator - Service Worker (PWA)
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 *
 * Purpose:
 *   - Makes the web generator installable as a Progressive Web App (browsers
 *     require a registered service worker with a fetch handler).
 *   - Lets the generator open and work offline after the first visit.
 *
 * Security notes:
 *   - Only same-origin GET requests are handled; cross-origin requests
 *     (e.g. Google Fonts) are left to the browser untouched.
 *   - Generated passwords never leave the page: they are produced locally
 *     with crypto.getRandomValues() and are never sent over the network,
 *     so there is nothing sensitive for this worker to cache.
 */

'use strict';

// Bump this value on every release so old caches are discarded.
const CACHE_VERSION = 'dnapass-v0.1.5';

// Core application shell. Required entries must exist or installation fails.
const REQUIRED_ASSETS = [
    './dnapass.html',
    './site.webmanifest'
];

// Nice-to-have assets. A missing file here must NOT break installation,
// so each one is cached individually and failures are ignored.
const OPTIONAL_ASSETS = [
    './',
    './index.html',
    './favicon.ico',
    './favicon2.ico',
    './favicon-256x256.png',
    './apple-touch-icon.png',
    './web-app-manifest-960x960.png',
    './web-app-manifest-960x958.png'
];

// Install: pre-cache the application shell.
self.addEventListener('install', (event) => {
    event.waitUntil((async () => {
        const cache = await caches.open(CACHE_VERSION);
        await cache.addAll(REQUIRED_ASSETS);
        await Promise.all(
            OPTIONAL_ASSETS.map((url) => cache.add(url).catch(() => undefined))
        );
        // Activate the new worker immediately instead of waiting for all tabs to close.
        await self.skipWaiting();
    })());
});

// Activate: remove caches from previous versions and take control of open pages.
self.addEventListener('activate', (event) => {
    event.waitUntil((async () => {
        const keys = await caches.keys();
        await Promise.all(
            keys
                .filter((key) => key.startsWith('dnapass-') && key !== CACHE_VERSION)
                .map((key) => caches.delete(key))
        );
        await self.clients.claim();
    })());
});

// Fetch strategy:
//   - Page navigations: network first (always get the latest release when
//     online), falling back to the cached page when offline.
//   - Other same-origin assets: stale-while-revalidate (fast from cache,
//     refreshed in the background).
self.addEventListener('fetch', (event) => {
    const request = event.request;

    if (request.method !== 'GET') return;

    const url = new URL(request.url);
    if (url.origin !== self.location.origin) return;

    if (request.mode === 'navigate') {
        event.respondWith(networkFirst(request));
        return;
    }

    event.respondWith(staleWhileRevalidate(request, event));
});

async function networkFirst(request) {
    const cache = await caches.open(CACHE_VERSION);
    try {
        const response = await fetch(request);
        if (response && response.ok) {
            cache.put(request, response.clone());
        }
        return response;
    } catch (error) {
        const cached = await cache.match(request, { ignoreSearch: true });
        if (cached) return cached;
        // Last resort while offline: open the generator itself.
        const fallback = await cache.match('./dnapass.html');
        if (fallback) return fallback;
        throw error;
    }
}

async function staleWhileRevalidate(request, event) {
    const cache = await caches.open(CACHE_VERSION);
    const cached = await cache.match(request, { ignoreSearch: true });

    const networkUpdate = fetch(request)
        .then((response) => {
            if (response && response.ok) {
                cache.put(request, response.clone());
            }
            return response;
        })
        .catch(() => undefined);

    if (cached) {
        // Keep the worker alive until the background refresh completes.
        event.waitUntil(networkUpdate);
        return cached;
    }

    const response = await networkUpdate;
    return response || Response.error();
}
