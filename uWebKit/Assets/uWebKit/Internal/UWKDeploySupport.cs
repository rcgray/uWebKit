#if UNITY_EDITOR

// We don't want to add a top level "Editor" folder for the uWebKit package
// so. we preprocess guard instead

using System.IO;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
 
public static class UWKDeploySupport
{
    static void removePaths(List<string> paths)
    {
    	foreach (var _path in paths)
    	{
    		string path = _path;
    		
    		if (Application.platform == RuntimePlatform.OSXEditor)
    			path = path.Replace("/", "\\");
    		
    		if (Directory.Exists(path))
    			Directory.Delete(path, true);

    		if (Directory.Exists(path))
    			Debug.LogError("Unable to remove deployment path: " + path);

    	}

    }
 
    [PostProcessBuild] 
    public static void OnPostProcessBuild(BuildTarget target, string path)
    {

    	if (path.Contains(".exe"))
    		path = path.Replace(".exe", "_Data");

		// osx deployment removal
    	List<string> osxDeploy = new List<string>();

    	// windows deployment removal
    	List<string> winDeploy = new List<string>();

    	bool windowsBuild = target == BuildTarget.StandaloneWindows || target == BuildTarget.StandaloneWindows64;

		osxDeploy.Add(path + "/Contents/Data/StreamingAssets/uWebKit/Mac/x86");
		osxDeploy.Add(path + "/Contents/Data/StreamingAssets/uWebKit/Mac/x86_64");
		osxDeploy.Add(path + "/Contents/Data/StreamingAssets/uWebKit/Windows/x86");
		osxDeploy.Add(path + "/Contents/Data/StreamingAssets/uWebKit/Windows/x86_64");

		winDeploy.Add(path + "/StreamingAssets/uWebKit/Mac/x86");
		winDeploy.Add(path + "/StreamingAssets/uWebKit/Mac/x86_64");
		winDeploy.Add(path + "/StreamingAssets/uWebKit/Windows/x86");
		winDeploy.Add(path + "/StreamingAssets/uWebKit/Windows/x86_64");

    	if (target == BuildTarget.StandaloneWindows)
    	{
    		winDeploy.Remove(path + "/StreamingAssets/uWebKit/Windows/x86");
    	}
    	else if (target == BuildTarget.StandaloneWindows64)
    	{
    		winDeploy.Remove(path + "/StreamingAssets/uWebKit/Windows/x86_64");
    	}
    	else if (target == BuildTarget.StandaloneOSXIntel)
    	{
    		osxDeploy.Remove(path + "/Contents/Data/StreamingAssets/uWebKit/Mac/x86");
    	}
    	else if (target == BuildTarget.StandaloneOSXIntel64)
    	{	
    		osxDeploy.Remove(path + "/Contents/Data/StreamingAssets/uWebKit/Mac/x86_64");
    	}

		if (windowsBuild)
			removePaths(winDeploy);
		else
			removePaths(osxDeploy);

    }

}

#endif 