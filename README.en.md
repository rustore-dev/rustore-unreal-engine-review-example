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
               background:linear-gradient(180deg,#ffffff,#f3f4f6);
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
               background:linear-gradient(180deg,#e9edf2,#ffffff);
               box-shadow:inset 0 2px 6px rgba(0,0,0,.10);">
    EN
  </span>

</div>
<!-- ────────────────────────────────────────────────────────────────── -->

> ⚠️ Do not use the "Code → Download" button on the GitFlic website – this method does not download files from Git LFS. [Cloning instructions](README_CLONE.en.md).

## RuStore Unreal Engine plugin for ratings and reviews

### [🔗 Developer documentation][10]

The RuStoreReview plugin allows users to leave a rating and review for your app in RuStore without leaving the app.

The repository contains the "RuStoreReview" and "RuStoreCore" plugins, as well as a demo application with usage examples and settings. Supports UE 5.3 and above.

### Installing the plugin into your project

1. Copy the contents of the _"Plugins"_ folder into the _"Plugins"_ folder inside your project. Restart Unreal Engine and check the "RuStoreReview" and "RuStoreCore" plugins in the list (Edit → Plugins → Project → Mobile).

2. In the _"YourProject.Build.cs"_ file, add the modules "RuStoreCore" and "RuStoreReview" to the PublicDependencyModuleNames list.

3. In project settings (Edit → Project Settings → Android), set the Minimum SDK Version to at least 24 and the Target SDK Version to at least 31.

### Building the example app

You can explore the demo application containing examples of all SDK methods:
- [README](unreal_example/README.en.md)
- [unreal_example](https://gitflic.ru/project/rustore/rustore-unreal-engine-review-example/file?file=unreal_example)

### Rebuilding the plugin

If you need to modify the plugin libraries' code, you can make changes and rebuild the included .aar files.

1. Open the Android project from the _"unreal_plugin_libraries"_ folder in your IDE.

2. Make the necessary changes.

3. Build the project using the gradle assemble command.

Upon successful build, the following files will be updated in the folders:
- _"unreal_example / Plugins / RuStoreReview / Source / RuStoreReview / ThirdParty / Android / libs"_
- _"unreal_example / Plugins / RuStoreCore / Source / RuStoreCore / ThirdParty / Android / libs"_

Files:
- RuStoreUnityReview.aar
- RuStoreUnityCore.aar

### Changelog

[CHANGELOG](CHANGELOG.en.md)

### Licensing Terms

This software, including source codes, binary libraries, and other files, is distributed under the MIT license. Licensing information is available in the [MIT-LICENSE](MIT-LICENSE.txt) document.

### Technical Support

Additional help and instructions are available on the page [rustore.ru/help/](https://www.rustore.ru/help/en/) or by email [support@rustore.ru](mailto:support@rustore.ru).

[10]: https://www.rustore.ru/help/en/sdk/reviews-ratings/unreal/10-5-1

[ru]: README.md
[en]: README.en.md
