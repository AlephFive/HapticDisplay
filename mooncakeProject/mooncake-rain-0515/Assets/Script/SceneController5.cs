using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneController5 : MonoBehaviour {
	
	public Camera m_camera;
	public GameObject page6;
	public GameObject man;
	public Light sun;
	public GameObject page7;
	public GameObject blackhole;
	public GameObject mountain;

	private int alpha = 0;
	private float falpha = 0f;
	private Renderer render6;
	private Renderer render7;
	private Renderer black;
	private bool fhide = false;
	private bool fdrag = true;
	private bool freturn = false;
	private int count = 0;
	private bool fblackhole = false;
	private bool fend = false;
	private bool fanmi = false;


	void Start () 
	{
		render6 = page6.GetComponent<Renderer> ();
		render6.material.color = new Color (1f, 1f, 1f, 0);
		render7 = page6.GetComponent<Renderer> ();
		render7.material.color = new Color (1f, 1f, 1f, 0);
		black = blackhole.GetComponent<Renderer> ();
		black.material.color = new Color (1f, 1f, 1f, 0);
	}
	

	void Update () 
	{
		if (fanmi) 
		{
			man.SetActive (false);
			Vector3 off = blackhole.transform.position - mountain.transform.position;
			if (mountain.transform.position.x < blackhole.transform.position.x) 
			{
				mountain.transform.Translate (off * 2 * Time.deltaTime, Space.Self);
				mountain.transform.localScale = mountain.transform.localScale / 1.2f;
			}
		}
		if (count >= 3)
			StartCoroutine (PlayPage7 ());
		
		if (m_camera.transform.position.x >= 273)
		{
			if (!fhide &&Input.GetMouseButton(0))
				StartCoroutine (PlayPage6 ());
			if (fhide &&Input.GetMouseButton(0))
				StartCoroutine (HidePage6 ());
			
		}

		if (fdrag) 
		{
			sun.color = Color.white * -2f / 11f * man.transform.position.y + Color.white * 5f / 11f;
			if (man.transform.position.y > 2.5)
				freturn = true;

			if(freturn)
			{
				float x = 279.4f - man.transform.position.x;
				float y = -3f - man.transform.position.y;
				float z = -6f - man.transform.position.z; 
				if (man.transform.position.y > -3)
					man.transform.Translate (new Vector3 (x, y, z) * 3 * Time.deltaTime, Space.Self);
				
				if (man.transform.position.y <= -2.9) 
				{
					count++;
					freturn = false;
				}
			}
		}

		if (fblackhole &&Input.GetMouseButton(0))
			StartCoroutine (HidePage7 ());

		if (fend)
			StartCoroutine (End ());
			
	}

	IEnumerator PlayPage6 ()
	{
		for ( ; alpha < 10; ) 
		{
			alpha = alpha + 1;
			falpha = alpha / 10f;
			render6.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		fhide = true;
		man.SetActive (true);
	}


	IEnumerator HidePage6 ()
	{
		for ( ; alpha > 0; ) 
		{
			alpha = alpha - 1;
			falpha = alpha / 10f;
			render6.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.05f);
		}
		yield return new WaitForSeconds (0.5f);
		page6.SetActive (false);
		fdrag = true;
	}


	IEnumerator PlayPage7 ()
	{
		page7.SetActive (true);
		for ( ; alpha < 10; ) 
		{
			alpha = alpha + 1;
			falpha = alpha / 10f;
			render6.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		fblackhole = true;
	}


	IEnumerator HidePage7 ()
	{
		for (; alpha > 0;) {
			alpha = alpha - 1;
			falpha = alpha / 10f;
			render6.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.05f);
		}
		yield return new WaitForSeconds (0.5f);
		Destroy (page7);
		blackhole.SetActive (true);
		fend = true;

	}

	IEnumerator End()
	{
		Vector3 blackScreen;
		Vector3 mouseScreen;
		while (Input.GetMouseButton (0)) {  

			blackScreen = Camera.main.WorldToScreenPoint (blackhole.transform.position);  
			mouseScreen = new Vector3(Input.mousePosition.x, Input.mousePosition.y, blackScreen.z); 
			float tx = Mathf.Abs(mouseScreen.x - blackScreen.x);
			float ty = Mathf.Abs (mouseScreen.y - blackScreen.y);
			if (tx < 100f && ty < 100f) {
				black.material.color = new Color (0, 0, 0, 1f);
				fanmi = true;
				fdrag = false;
			}

			yield return new WaitForFixedUpdate();  
		}
	}

}