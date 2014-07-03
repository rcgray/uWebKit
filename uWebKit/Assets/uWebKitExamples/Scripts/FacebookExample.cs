
using System;
using System.Collections;
using System.Collections.Generic;

using UnityEngine;
using UWK;

public class FacebookExample : MonoBehaviour
{	
	UWKWebView view;

	void OnLoggedIntoFacebook(UWKWebView view)
	{
		this.view = view;
		getFriends();
	}

	void getFriends()
	{
		var request = new FBRequest(view, "/me/friends");

		request.OnSuccess += delegate(UWKWebView _view, string json, Dictionary<string, object> values) 
		{
			Debug.Log("On Success: " + json);
		};

		request.OnError += delegate(UWKWebView _view, string json, Dictionary<string, object> values) 
		{
			Debug.Log("On Error: " + json);
		};		

		request.Send();		
	}

}


