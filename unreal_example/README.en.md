<!-- ── Language switch (EN active) ──────────────────────────────────── -->
<div align="left" style="margin:0 0 14px 0;">

  <span style="display:inline-block;
               padding:.28rem .6rem;
               border:1px solid rgba(0,0,0,.18);
               border-radius:10px 0 0 10px;
               font-weight:400;
               font-size:12px;
               letter-spacing:.06em;
               color:#111827;
               background:linear-gradient(180deg,#ffffff,#e9edf2);
               box-shadow:0 1px 0 rgba(0,0,0,.06);">
    [RU][ru]
  </span><span style="display:inline-block;
               margin-left:-1px;
               padding:.28rem .6rem;
               border:1px solid rgba(0,0,0,.14);
               border-radius:0 10px 10px 0;
               font-weight:400;
               font-size:12px;
               letter-spacing:.06em;
               background:linear-gradient(180deg,#f3f4f6,#ffffff);
               box-shadow:inset 0 2px 6px rgba(0,0,0,.10);">
    EN
  </span>

</div>
<!-- ────────────────────────────────────────────────────────────────── -->

## RuStore Unreal Engine plugin for reviews and ratings

### [🔗 Developer documentation][10]

- [SDK operating conditions](#SDK-operating-conditions)
- [Preparing required parameters](#Preparing-required-parameters)
- [Setting up the sample application](#Setting-up-the-sample-application)
- [Usage scenario](#Usage-scenario)
- [Distribution conditions](#Distribution-conditions)
- [Technical support](#Technical-support)


### SDK operating conditions

To use the reviews and ratings SDK, the following conditions must be met:

1. Android OS version 7.0 or higher.

2. The RuStore app is installed on the user's device.

3. The RuStore version on the user's device is up to date.

4. The user is logged into RuStore.

5. The app must be published in RuStore.


### Preparing required parameters

1. `applicationId` - a unique identifier of the app in the Android system in reverse domain name format (example: ru.rustore.sdk.example).

2. `*.keystore` - a key file used for [signing and authenticating an Android app](https://www.rustore.ru/help/en/developers/publishing-and-verifying-apps/app-publication/apk-signature/).


### Setting up the sample application

1. In project settings (Edit → Project Settings → Platforms → Android), specify the `applicationId` in the "Android Package Name" field — the app code from the RuStore developer console.

2. In project settings (Edit → Project Settings → Platforms → Android), under "Distribution Signing", specify the location and parameters of the previously prepared `*.keystore` file.


### Usage scenario

#### Preparing to launch the app review

Tapping the `RequestReviewFlow` button initiates the [process of preparing for launching the app review][20].

![Preparing to launch the app review](images/01_request_review_flow.png)


#### Launching the app review

Tapping the `LaunchReviewFlow` button initiates the [process of launching the app review][30].

![Launching the app review](images/02_launch_review_flow.png)


### Distribution conditions

This software, including source codes, binary libraries, and other files, is distributed under the MIT license. Licensing information is available in the [MIT-LICENSE](../MIT-LICENSE.txt) document.


### Technical support

Additional help and instructions are available on the page [rustore.ru/help/](https://www.rustore.ru/help/en/) and by email at [support@rustore.ru](mailto:support@rustore.ru).

[10]: https://www.rustore.ru/help/en/sdk/reviews-ratings/unreal/10-5-1
[20]: https://www.rustore.ru/help/en/sdk/reviews-ratings/unreal/10-5-1#prestart
[30]: https://www.rustore.ru/help/en/sdk/reviews-ratings/unreal/10-5-1#start

[ru]: README.md
[en]: README.en.md
