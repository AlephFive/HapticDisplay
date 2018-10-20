 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneController3 : MonoBehaviour {

	public GameObject fly;
	public GameObject chain;
	public GameObject man1;
	public GameObject man2;
	public GameObject man3;
	public Camera m_camera;
	public GameObject page4;


	private bool fmove = false;
	private bool fhide = false;
	private float speed = 0;
	private int alpha = 0;
	private float falpha = 0f;
	private Renderer render4;


	void Start ()
	{
		render4 = page4.GetComponent<Renderer> ();
		render4.material.color = new Color (1f, 1f, 1f, 0);

	}

	void Update ()
	{
		if (m_camera.transform.position.x >= 126 && m_camera.transform.position.x < 168) {
			fly.SetActive (true);
			if (fly.transform.position.x > 10) {
				chain.SetActive (false);
				man1.SetActive (false);
				man2.SetActive (true);
				if (man2.transform.position.y > -5)
					man2.transform.Translate (Vector3.down * 5 * Time.deltaTime);
				else {
					man2.SetActive (false);
					man3.SetActive (true);
					if (!fhide && Input.GetMouseButton(0))
						StartCoroutine (PlayPage4 ());
					if (fhide && Input.GetMouseButton(0))
						StartCoroutine (HidePage4 ());
				}
				if (fly.transform.position.x > 30)
					fly.SetActive (false);
			}
			fly.transform.Translate (Vector3.right * 5 * Time.deltaTime);
		}
		if (fmove && man3.transform.position.x > 136) 
		{
			man3.SetActive (false);
			m_camera.transform.Translate (Vector3.right * speed * Time.deltaTime, Space.Self);
			if (m_camera.transform.position.x < 148)
			{
				speed++;
			} 
			else
			{
				if (speed != 0)
					speed--;
			}
		}
		if (fmove && m_camera.transform.position.x > 168) 
		{
			fmove = false;			
		}
	}
		

	IEnumerator PlayPage4 ()
	{
		for ( ; alpha < 10; ) 
		{
			alpha = alpha + 1;
			falpha = alpha / 10f;
			render4.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		fhide = true;

	}


	IEnumerator HidePage4 ()
	{
		for ( ; alpha > 0; ) 
		{
			alpha = alpha - 1;
			falpha = alpha / 10f;
			render4.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.05f);
		}
		yield return new WaitForSeconds (0.5f);
		fmove = true;
		page4.SetActive (false);
	}

}                                                        