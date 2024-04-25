# Nvidia API Library

Since I'm almost certain you cannot redistribute nvidia's api, I'm putting this directory here to denote that vel3d can pull in and utilize nvidia's api, you just need to go out, obtain it from nvidia's website, build it, and include it here as follows:

- /bin/{windows_amd64_Release|linux_amd64_Release}/nvapi.lib|.a
- /include/nvapi/{all_public_header_files}

I had originally added the nvidia api so that I could create custom profiles to turn certain features off. It was found in the early days of Ampere that opengl threaded optimization was causing a micro stutter in this library. Therefore nvidia api was included and I added code to disable thread control. If you include nvidia api, the renderer will run without threaded optimization.
