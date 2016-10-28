using UnityEngine;
using System.Collections;

public class NavCharScript : MonoBehaviour {

	NavMeshAgent agent;
	Vector3 toiletPt;
	Vector3 elevatePt;
	Vector3 HydrantPt;

	void Start ()
	{
		agent = GetComponent<NavMeshAgent>();
		elevatePt = new Vector3 (-954.2f, 0f, 148.6f);
		toiletPt = new Vector3 (-1335.4f, 0f, 363.2f);
		HydrantPt = new Vector3 (-2082.45f, 0f, -54f);
	}

	public void setToiletDest()
	{
		agent.SetDestination (toiletPt);
	}

	public void setElevateDest()
	{
		agent.SetDestination (elevatePt);
	}

	public void setHydrantDest()
	{
		agent.SetDestination (HydrantPt);
	}

	void Update () 
	{
		if(Input.GetMouseButtonDown (0))
		{
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);
			RaycastHit hit;

			if(Physics.Raycast(ray, out hit, 10000))
			{
				agent.SetDestination (hit.point);
			}
		}
	}
}
