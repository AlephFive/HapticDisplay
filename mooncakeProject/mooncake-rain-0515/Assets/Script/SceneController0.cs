using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SceneController0 : MonoBehaviour {

	public RawImage page1;
	public GameObject page2;
	public Camera m_camera;

	private Renderer render2;
	private Renderer render3;
	private int alpha = 0;
	private float falpha = 0f;
	private float speed = 0f;

	private bool fpage1 = true;
	private bool fpage2 = false;
	private bool fmove = false;
	private bool fhide2 = false;


	void Start () 
	{
		render2 = page2.GetComponent<Renderer> ();
		render2.material.color = new Color (1f, 1f, 1f, 0);
	}


	void Update ()
	{
		//右滑触发page1消失
		if (fpage1 && Input.GetMouseButton(0) )
			StartCoroutine (PlayPage1 ());
		
		//右滑触发page2消失，进入scene1
		if (fpage2 && Input.GetMouseButton(0)) 
			StartCoroutine (PlayPage2 ());

		//右滑触发page2消失，进入scene1
		if (fhide2 && Input.GetMouseButton (0)) {
			StartCoroutine (HidePage2 ());
			page2.SetActive (false);
		}
		

		//移动摄像机到下一幕
		if (fmove && m_camera.transform.position.x <= 66) 
		{
			m_camera.transform.Translate (Vector3.right * speed * Time.deltaTime);
			if (m_camera.transform.position.x < 50)
			{
				speed++;
			} 
			else
			{
				if (speed != 0)
					speed--;
			}
		}
		else if (m_camera.transform.position.x >= 66) 
		{
			fmove = false;	
			fpage2 = true;
		}
	}


	IEnumerator PlayPage1 ()
	{
		yield return new WaitForSeconds (0.5f); 
		page1.CrossFadeAlpha (0,0.5f,true);
		yield return new WaitForSeconds (0.5f);
		fpage1 = false;
		fmove = true;
	}
		

	IEnumerator PlayPage2 ()
	{
		yield return new WaitForSeconds (0.5f);
		alpha = 0;
		for ( ; alpha < 10; ) 
		{
			alpha = alpha + 1;
			falpha = alpha / 10f;
			render2.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		yield return new WaitForSeconds (0.5f);
		fhide2 = true;
	}

	IEnumerator HidePage2 ()
	{
		yield return new WaitForSeconds (0.5f);
		{
			alpha = alpha - 1;
			falpha = alpha / 10f;
			render2.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		yield return new WaitForSeconds (0.5f);

	}

}