using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneController4 : MonoBehaviour {

	public Camera m_camera;
	public GameObject wife;
	public GameObject man;
	public GameObject man_r;
	public GameObject dead;
	public GameObject god;
	public GameObject page5;
	public GameObject thunder;

	private bool fmove = false;
	private bool fhide = false;
	private bool fmove2 = false;
	private float speed = 0;
	private int alpha = 0;
	private float falpha = 0f;
	private Renderer render5;


	void Start ()
	{
		render5 = page5.GetComponent<Renderer> ();
		render5.material.color = new Color (1f, 1f, 1f, 0);

	}


	// Update is called once per frame
	void Update () 
	{
		if (m_camera.transform.position.x >= 168 && wife.transform.position.x > 169)
			wife.transform.Translate (Vector3.left * 6 * Time.deltaTime);
		if (wife.transform.position.x <= 169) 
		{
			if (!fhide &&Input.GetMouseButton(0))
				StartCoroutine (PlayPage5 ());
			if (fhide &&Input.GetMouseButton(0))
				StartCoroutine (HidePage5 ());
		}
		if (!fmove && man_r.transform.position.x > 174 && m_camera.transform.position.x < 273) 
			StartCoroutine (Dead ());

		if (fmove &&Input.GetMouseButton(0))
			fmove2 = true;

		if (fmove2)
		{
			m_camera.transform.Translate (Vector3.right * speed * Time.deltaTime, Space.Self);
			if (m_camera.transform.position.x < 273) {
				if (m_camera.transform.position.x < 222)
					speed++;
				else {
					if (speed != 0)
						speed--;
				}
			} else {
				fmove = false;
				fmove2 = false;
			}
		}
	}


	IEnumerator PlayPage5 ()
	{
		for ( ; alpha < 10; ) 
		{
			alpha = alpha + 1;
			falpha = alpha / 10f;
			render5.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.1f);
		}
		fhide = true;
		man.SetActive (false);
		wife.SetActive (false);
		man_r.SetActive (true);
		god.SetActive (true);

	}


	IEnumerator HidePage5 ()
	{
		for ( ; alpha > 0; ) 
		{
			alpha = alpha - 1;
			falpha = alpha / 10f;
			render5.material.color = new Color (1f, 1f, 1f, falpha);
			yield return new WaitForSeconds (0.05f);
		}
		yield return new WaitForSeconds (0.5f);
		page5.SetActive (false);
	}


	IEnumerator Dead ()
	{
		thunder.SetActive (true);
		dead.SetActive (true);
		man_r.SetActive (false);
		yield return new WaitForSeconds (0.5f);
		thunder.SetActive (false);
		fmove = true;
	}

}
