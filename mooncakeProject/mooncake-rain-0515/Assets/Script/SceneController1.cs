using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SceneController1 : MonoBehaviour {

	public Camera m_camera;
	public GameObject head;
	public GameObject man_1;
	public GameObject man_2;
	public GameObject soul;
	public GameObject chain;
	public GameObject death;
	public GameObject drag;
	public GameObject page3;
	public GameObject page2;

	private int alpha = 10;
	private int palpha = 0;
	private float falpha = 0f;
	private float speed = 0f;
	private Renderer render3;
	private Renderer[] renders;
	private Renderer[] nrenders;
	private Renderer[] srenders;

	private bool fplay = true;
	private bool fdeathmove = false;
	private bool fpage3 = false;
	private bool fhide = false;
	private bool fmove = false;


	void Start ()
	{
		chain.SetActive (false);
		renders = man_1.GetComponentsInChildren<Renderer> ();
		nrenders = man_2.GetComponentsInChildren<Renderer> ();
		srenders = soul.GetComponents<Renderer> ();
		render3 = page3.GetComponent<Renderer> ();

		foreach (Renderer render in nrenders) 
			render.material.color = new Color (1f, 1f, 1f, 0);

		foreach (Renderer render in srenders) 
			render.material.color = new Color (1f, 1f, 1f, 0);

		page3.SetActive (false);
		
	}

	void Update () 
	{
		//播放本幕动画
		if (m_camera.transform.position.x >= 66 && fplay && page2.activeSelf == false)
			StartCoroutine (PlayScene1 ()); 

		//播放本幕动画2-死神移动
		if (fdeathmove && death.transform.position.x < 67) 
		{
			death.transform.Translate (Vector3.right * 5 * Time.deltaTime);
			chain.transform.Rotate (0f, 0f, -100 * Time.deltaTime, Space.Self);
		}
		if (fdeathmove && death.transform.position.x > 66) 
		{
			fdeathmove = false;
			fpage3 = true;
		}

		//拖拽死神出本页播放page3
		if (fpage3 && drag.transform.position.x > 74) 
		{
			page3.SetActive (true);
			StartCoroutine (PlayPage3 ()); 

		}

		//右滑触发page3消失，进入scene2
		if (fhide && Input.GetMouseButton(0)) 
		{
			fpage3 = false;
			drag.SetActive (false);
			man_2.SetActive (false);
			StartCoroutine (HidePage3 ());
		}

		//移动摄像机到下一幕
		if (fmove && m_camera.transform.position.x <= 81) 
		{
			m_camera.transform.Translate (Vector3.right * speed * Time.deltaTime, Space.Self);
			if (m_camera.transform.position.x < 75)
			{
				speed++;
			} 
			else
			{
				if (speed != 0)
					speed--;
			}
		}
		if (fmove && m_camera.transform.position.x > 81) 
		{
			fmove = false;			
		}



	}


	IEnumerator PlayScene1 () 
	{
		//抬头
		yield return new WaitForSeconds (2f);
		head.transform.rotation= Quaternion.Euler (0, 0, -10.0f);

		//死神打开锁链，主角倒下
		yield return new WaitForSeconds (0.5f);
		chain.SetActive (true);
		yield return new WaitForSeconds (0.5f);
		man_1.transform.rotation= Quaternion.Euler (0, 0, -90.0f);

		//灵魂和尸体出现
		for ( ; alpha > 0; ) 
		{
			alpha = alpha - 1;
			falpha = alpha / 10f;
			foreach (Renderer render in renders) 
			{
				render.material.color = new Color (1f, 1f, 1f, falpha);
			}
			foreach (Renderer render in nrenders) 
			{
				render.material.color = new Color (1f, 1f, 1f, 1f - falpha);
			}
			foreach (Renderer render in srenders) 
			{
				render.material.color = new Color (1f, 1f, 1f, 1f - falpha);
			}
			yield return new WaitForSeconds (0.1f);
		}

		//死神移动
		fdeathmove = true;
		fplay = false;
	}


	IEnumerator PlayPage3 ()
	{
		for ( ; palpha < 10; ) 
		{
			palpha = palpha + 1;
			falpha = palpha / 10f;
			render3.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		yield return new WaitForSeconds (0.5f);
		fhide = true;
	}

	IEnumerator HidePage3 ()
	{
		for ( ; palpha > 0; ) 
		{
			palpha = palpha - 1;
			falpha = palpha / 10f;
			render3.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.05f);
		}
		yield return new WaitForSeconds (0.5f);
		fmove = true;
	}

}