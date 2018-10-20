using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Exit : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButton (1))
			//SceneManager.LoadScene (0);
		//if (Input.GetAxis("Mouse ScrollWheel") < -5f)
			Application.Quit ();
			
	}
}
